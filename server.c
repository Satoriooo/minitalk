/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:20 by shirose           #+#    #+#             */
/*   Updated: 2026/04/13 20:14:28 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

	if (n == 7)
		c = 0;
	c = c | signum << n;
	return (c);
}

void my_handler(int signum)
{
	static int	idx = 0;
	char		c;

	if (signum == SIGUSR1)
		signum = 0;
	else
		signum = 1;
	c = bits_to_char(signum, 7 - idx);
	idx++;
	if (idx == 8)
	{
		write(1, &c, 1);
		idx = 0;
	}
}

int main(int ac, char **av)
{
	struct sigaction sa;

	sa.sa_handler = my_handler;
	sigemptyset(&sa.sa_mask);

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (1);
	else if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (1);
	while (1)
	{
	}
	return (0);
}