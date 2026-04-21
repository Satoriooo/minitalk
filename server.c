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

typedef struct s_data
{
	volatile sig_atomic_t	error_state;
	volatile sig_atomic_t	client_pid;
	volatile sig_atomic_t	pid_occupied;
	volatile sig_atomic_t	bit;
	volatile sig_atomic_t	busy;
}	t_data;

static t_data	g_data;

static void	error_handler(char *msg)
{
	print_error(msg);
	g_data.error_state = 1;
}

static char	bits_to_char(int signum)
{
	static unsigned char	c = 0;

	c = c << 1 | signum;
	return (c);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	ft_putstr_fd("signal_handler called\n", 1);
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
	static size_t	n;

	if (i == 0)
		n = 0;
	n = n << 1 | g_data.bit;
	return (n);
}

static void	reset_struct(void)
{
	g_data.bit = 0;
	g_data.client_pid = 0;
	g_data.error_state = 0;
	g_data.pid_occupied = 0;
	g_data.busy = 0;
}

static void	sigaction_setup(struct sigaction *sa)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
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

static void	handle_character(size_t *i, size_t *idx, size_t *len, char **str)
{
	char	c;

	if (*i == 64)
	{
		*str = malloc(*len);
		if (!*str)
		{
			error_handler("Malloc failed.");
			return ;
		}

	}
	if (*idx < *len)
	{
		c = bits_to_char(g_data.bit);
		if (*i > 64 && (*i + 1) % 8 == 0)
			(*str)[(*idx)++] = c;
	}
	if (*idx == *len)
	{
		ft_putstr_fd(*str, 1);
		free(*str);
		*str = NULL;
		*i = -1;
		*idx = 0;
		*len = 0;
		g_data.pid_occupied = 0;
	}
}

static void	reset_client_state(size_t *i, size_t *idx, size_t *len, char **s)
{
	reset_struct();
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	*i = 0;
	*idx = 0;
	*len = 0;
}

static void	wait_for_signal(size_t *i, size_t *idx, size_t *len, char **s)
{
	int	wait_time;

	wait_time = 0;
	while (g_data.busy == 0 && g_data.error_state == 0)
	{
		usleep(100);
		wait_time++;
		if (g_data.pid_occupied == 1 && wait_time > 10000)
		{
			reset_client_state(i, idx, len, s);
			wait_time = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;
	size_t				i;
	size_t				idx;
	size_t				len;
	char				*str;

	sigaction_setup(&sa);
	str = NULL;
	reset_client_state(&i, &idx, &len, &str);
	while (1)
	{
		wait_for_signal(&i, &idx, &len, &str);
		if (g_data.error_state)
			return (1);
		g_data.busy = 0;
		if (i < 64)
			len = get_strlen(i);
		else
			handle_character(&i, &idx, &len, &str);
		i++;
		if (kill(g_data.client_pid, SIGUSR1) == -1)
			reset_client_state(&i, &idx, &len, &str);
	}
	return (0);
}
