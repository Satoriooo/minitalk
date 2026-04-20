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
; //TODO not safe for signal-safety man perspective , can u  se flag and exit in main instad
}

static char	bits_to_char(int signum)
{
	// static int x = 0;
//	printf("-- bits_to_char ... Call: %d --\n", x++);
	
	static int n = 0;
	static unsigned char	c = 0;
	if (n == 7)
		c = 0;
//	printf("bit: %d\n", signum);
	c = c << 1 | signum;
//	printf("== bit in int ... %d ==\n", c);
	return (c);
}

#include <stdio.h>

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid <= 0)
		error_handler("Invalid PID.");
	printf("state: %d, client pid %d\n", g_data.pid_occupied, g_data.client_pid);
	if (g_data.pid_occupied == 1 && g_data.client_pid != info->si_pid)
		return ;
	if (g_data.pid_occupied == 0)
		g_data.client_pid = info->si_pid;
	{
		printf("Client PID: %d\n", info->si_pid);
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
	// static int x = 0;
//	printf("get_strlen ... call: %d\n", x++);

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
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sa->sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
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

	sigaction_setup(&sa);

	// print_pid();
	// sa.sa_sigaction = &signal_handler;
	// sigemptyset(&sa.sa_mask);
	// sigaddset_handler(&sa.sa_mask, SIGUSR1);
	// sigaddset(&sa.sa_mask, SIGUSR1);
	// sigaddset(&sa.sa_mask, SIGUSR2);
	// sa.sa_flags = SA_SIGINFO;
	// sigaction(SIGUSR1, &sa, NULL);
	// sigaction(SIGUSR2, &sa, NULL);
	// reset_struct();
	i = 0;
	digit = 0;
	idx = 0;
	while (1)
	{
		while (g_data.busy == 0)
			usleep(10);
    	g_data.busy = 0;
		
		printf("-- While loop call ... i: %zu--\n", i);
		if (i < 64)
			len = get_strlen(i);
		else if (i >= 64)
		{
			if (i == 64)
			{
				printf("-- Malloc call --\n");
				printf("len: %zu\n", len);

				str = malloc(len + 1);
				if (!str)
					error_handler("Malloc failed.");
				str[len] = '\0';
			}
			static size_t z = 0;
			printf("-- before: bits_to_char ... Call: %zu, i: %zu --\n", z++, i);
			printf("-- idx: %zu, len: %zu --\n", idx, len);
			if (idx < len)
			{
				printf("-- cp: bits_to_char ... Call: %zu, i: %zu --\n", z++, i);

				c = bits_to_char(g_data.bit);
				if (i > 64 && (i + 1) % 8 == 0)
				{
					str[idx++] = c;
					printf("c: %c\n", c);
				}
				c = 0;
			}
			if (idx == len)
			{
				// printf("-- ft_putstr --\n");
				ft_putstr_fd(str, 1);
				free(str);
				str = NULL;
				i = -1;
				idx = 0;
				len = 0;
				g_data.pid_occupied = 0;
				// g_data.client_pid = 0;
			}
		}
		if (kill(g_data.client_pid, SIGUSR1) == -1)
			return (1);
		if (idx > 0 && idx == len)
			g_data.client_pid = 0;
		i++;
	}
	return (0);
}
