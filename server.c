/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:20 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 00:02:38 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static volatile sig_atomic_t g_state = 0;

static int	error_handler(char *msg)
{
	print_error(msg);
	exit (1);
}

static char bits_to_char(int signum, int n)
{
	static char	c = 0;

	if (signum == SIGUSR1)
		signum = 0;
	else
		signum = 1;
	if (n == 7)
		c = 0;
	c = c | signum << n;
	return (c);
}

static void	set_state(pid_t *current_pid, int *idx, char *c, pid_t new_pid)
{
	*current_pid = new_pid;
	*idx = 0;
	*c = 0;
}

static void my_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t	current_pid = 0;
	static int		idx = 0;
	char			c;

	(void) context;
	if (info->si_pid <= 0)
		error_handler("Invalid PID.");
	if (current_pid != 0 && current_pid != info->si_pid)
		set_state(&current_pid, &idx, &c, info->si_pid);
	if (current_pid == 0)
    	current_pid = info->si_pid;
	if (current_pid != info->si_pid)
    	return ;
	c = bits_to_char(signum, 7 - idx++);
	if (idx == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			current_pid = 0;
		idx = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		set_state(&current_pid, &idx, &c, 0);
}

int main()
{
	struct sigaction	sa;
	
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = &my_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
	|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_handler("Failed to initialize sigaction.");
	while (1)
		pause();
	return (0);
}