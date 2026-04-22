/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:34:11 by shirose           #+#    #+#             */
/*   Updated: 2026/04/22 13:58:36 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	exit_error(char *msg)
{
	print_error(msg);
	exit(1);
}

char	bits_to_char(int signum)
{
	static unsigned char	c = 0;

	c = c << 1 | signum;
	return (c);
}

size_t	get_strlen(int i)
{
	static size_t	n;

	if (i == 0)
		n = 0;
	n = n << 1 | g_data.bit;
	return (n);
}

void	sigaction_setup(struct sigaction *sa)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa->sa_sigaction = &signal_handler;
	sigemptyset(&sa->sa_mask);
	if (sigaddset(&sa->sa_mask, SIGUSR1) == -1)
		exit_error("Failed sigaddset.");
	if (sigaddset(&sa->sa_mask, SIGUSR2) == -1)
		exit_error("Failed sigaddset.");
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		exit_error("Failed sigaction.");
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		exit_error("Failed sigaction.");
	reset_struct();
}

void	reset_client_state(size_t *i, size_t *idx, size_t *len, char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	*i = 0;
	*idx = 0;
	*len = 0;
}
