/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 01:06:27 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	is_int(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}
void	signal_confirmation(int signum, siginfo_t *si, void *context)
{
	(void)si;
	(void)context;
	// static int n = 0;
	// printf("Call: n = %d\n", n++);
	// if (signum == SIGUSR1)
	// 	ft_putstr_fd("Confirm: Received SIGUSR1.\n", 1);
	// else if (signum == SIGUSR2)
	// 	ft_putstr_fd("Confirm: Received SIGUSR2.\n", 1);
	// else
	// 	ft_putstr_fd("Unknown signal received.\n", 1);
	g_state = 0;
}

int error_handler(char *msg)
{
	ft_putstr_fd(msg, 1);
	exit (1);
}

void kill_handler(int pid, int sig)
{
	if (kill(pid, sig) == -1)
		error_handler("kill function failed.");
}

void send_char(unsigned char c, int pid)
{
	int	i;
	int cnt;

	i = 8;
	while (--i >= 0)
	{
		if ((c >> i & 1) == 0)
			kill_handler(pid, SIGUSR1);
		else
			kill_handler(pid, SIGUSR2);
		g_state = 1;
		cnt = 0;
		while(g_state == 1)
		{
			usleep(10);
			cnt++;
			if (cnt == 50)
				error_handler("Time out: Can't receive confirmation.");
		}
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					i;
	int					pid;

	if (ac != 3)
	{
		error_handler("Invalid number of parameters.");
		return (1);
	}
	if (ft_strlen(av[1]) > 12 || is_int(av[1]) == -1 || ft_atoi(av[1]) < 0)
	{
		print_error("Invalid PID.");
		return (1);
	}
	pid = ft_atoi(av[1]);
	sa.sa_sigaction = &signal_confirmation;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_handler("Client failed to send signal.");
	i = 0;
	while (av[2][i])
	{
		send_char((unsigned char)av[2][i++], pid);
	}
	return (0);
}
