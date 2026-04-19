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

t_data g_data;

static void	error_handler(char *msg)
{
	print_error(msg);
	g_data.error_state = 1;
; //TODO not safe for signal-safety man perspective , can u  se flag and exit in main instad
}

static char	bits_to_char(int signum, int n)
{
	static int x = 0;
	printf("--bits_to_char-- Call: %d\n", x++);
	
	static char	c = 0;
	if (n == 7)
		c = 0;
	printf("bit: %d\n", signum);
	c = c | signum << n;
	return (c);
}

static void	set_state(pid_t *current_pid, int *idx, char *c, pid_t new_pid)
{
	*current_pid = new_pid;
	*idx = 0;
	*c = 0;
}
#include <stdio.h>
static void	my_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	current_pid = 0;
	static int		idx = 0;
	char			c = 0;
	static size_t	i = 0;

	(void)context;
	if (info->si_pid <= 0)
		error_handler("Invalid PID.");
	if (current_pid == 0)
		current_pid = info->si_pid;
	if (current_pid != info->si_pid)
		return ;

	static size_t	tmp_len = 0;
	static size_t	len = 0;
	static size_t	digit = 0;
	static char 	*str = NULL;

	if (signum == SIGUSR1)
		signum = 0;
	else
		signum = 1;

	if (digit < 64)
		get_strlen(signum);

	else if (digit == 64 && len == 0)
	{
		len = tmp_len;
		printf("len: %zu\n", len);
		if (!str)
			str = malloc(sizeof(char) * len + 1);
		if (!str)
			exit(1);
		printf("malloc successful! size: %zu\n", len);
	}
	if (len != 0 && i <= len)
	{
		c = bits_to_char(signum, 7 - idx++);
		if (idx == 8)
		{
			printf("== char c: %c==\n", c);
			str[i++] = c;
			idx = 0;
			c = 0;
		}
	}
	if (len != 0 && i == len + 1)
	{
		static int y = 0;
		printf("-- Y Call : %d--, signum: %d\n", y++, signum);
		printf("str: %s, str[%zu]: %c\n", str, len, str[len]);
		ft_putstr_fd(str, 1);
		free(str);
		str = NULL;
		len = 0;
		digit = 0;
		tmp_len = 0;
		i = 0;
		current_pid = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		set_state(&current_pid, &idx, &c, 0);
}

void	get_strlen(int len)
{
	
}

int	main(void)
{
	struct sigaction	sa;
	size_t 				len;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = &my_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask))
		error_handler("Failed to initialize signal set.");
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_handler("Failed to initialize sigaction.");
	while (1)
	{
		if(g_data.error_state == 1)		
			error_handler(1);
		if(g_data.bit != -1)
			get_strlen(&len); // i = 64 -> bit = -1
	}
	return (0);
}
