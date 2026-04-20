/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:16:30 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 19:16:30 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#define BUFFER_SIZE 20097152

static t_data g_data;

static void	error_handler(char *msg)
{
	print_error(msg);
	g_data.error_state = 1;
}

static char	bits_to_char(int signum)
{	
	static int n = 0;
	static unsigned char	c = 0;
	if (n == 7)
		c = 0;
	c = c << 1 | signum;
	return (c);
}

#include <stdio.h>

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid <= 0)
		error_handler("Invalid PID.");
	if (g_data.pid_occupied == 1 && g_data.client_pid != info->si_pid)
		return ;
	if (g_data.pid_occupied == 0)
	{
		g_data.client_pid = info->si_pid;
		g_data.pid_occupied = 1;
	}
	if (signum == SIGUSR1)
		g_data.bit = 0;
	else
		g_data.bit = 1;
	g_data.busy = 1;
}

size_t	get_strlen(int i)
{
	static size_t n;
	if (i == 0)
		n = 0;

	n = n << 1 | g_data.bit;
	return (n);
}

static void reset_struct()
{
	g_data.bit = 0;
	g_data.client_pid = 0;
	g_data.error_state = 0;
	g_data.pid_occupied = 0;
	g_data.busy = 0; 
}

static void print_pid()
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

static void sigaction_setup(struct sigaction *sa)
{
	print_pid();
	sa->sa_sigaction = &signal_handler;
	sigemptyset(&sa->sa_mask);
	if (sigaddset(&sa->sa_mask, SIGUSR1) == -1)
		error_handler("Failed sigaddset.");
	if (sigaddset(&sa->sa_mask, SIGUSR2) == -1)
		error_handler("Failed sigaddset.");
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		error_handler("Failed sigaction.");
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		error_handler("Failed sigaction.");
	reset_struct();
}

int	main(void)
{
	struct sigaction	sa;
	size_t 				len;
	char 				*str;
	size_t	i;
	size_t	digit;
	char c;
	size_t	idx;

	int pid;

	sigaction_setup(&sa);

	i = 0;
	digit = 0;
	idx = 0;
	while (1)
	{
		while (g_data.busy == 0)
			usleep(10);
    	g_data.busy = 0;
		pid = g_data.client_pid;

		if (i < 64)
			len = get_strlen(i);
		else if (i >= 64)
		{
			if (i == 64)
			{
				str = malloc(len + 1);
				if (!str)
					error_handler("Malloc failed.");
				str[len] = '\0';
			}
			if (idx < len)
			{
				c = bits_to_char(g_data.bit);
				if (i > 64 && (i + 1) % 8 == 0)
					str[idx++] = c;
				c = 0;
			}
			if (idx == len)
			{
				ft_putstr_fd(str, 1);
				free(str);
				str = NULL;
				i = -1;
				idx = 0;
				len = 0;
				g_data.pid_occupied = 0;
			}
		}
		if (kill(pid, SIGUSR1) == -1)
			return (1);
		if (idx > 0 && idx == len)
			g_data.client_pid = 0;
		i++;
	}
	return (0);
}
