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

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-', fd);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar((nb % 10) + '0', fd);
}

char bits_to_char(int signum, int n)
{
	static char c = 0;

	if (signum == SIGUSR1)
		signum = 0;
	else
		signum = 1;
	if (n == 7)
		c = 0;
	c = c | signum << n;
	return (c);
}

void my_handler(int signum, siginfo_t *info, void *context)
{
	static pid_t current_pid = 0;
	static int	idx = 0;
	char		c;

	(void) context;
	if (current_pid != 0 && current_pid != info->si_pid)
	{
		current_pid = info->si_pid;
		idx = 0;
		c = 0;
	}
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
		kill(info->si_pid, SIGUSR1);
}

int main()
{
	struct sigaction sa;
	
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = &my_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}