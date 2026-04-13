/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/13 17:33:38 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void send_char(char c, int pid)
{
	int i;

	i = 8;
	while (--i >= 0)
	{
		if ((c >> i & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(SLEEP_TIME);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	if (ac != 3)
	{
		print_error("Invalid number of parameters.");
		return (1);
	}
	if (ft_strlen(av[1]) > 12 || is_int(av[1]) == -1 || ft_atoi(av[1]) < 0)
	{
		print_error("Invalid PID");
		return (1);
	}
	pid = ft_atoi(av[1]);

	i = 0;
	while (av[2][++i])
		send_char(av[2][i], pid);
	return (0);
}