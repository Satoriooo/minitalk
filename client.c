/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/12 19:00:38 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


int ft_strlen(char *s)
{
	int n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	sign;
	size_t	nb;

	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

void send_length(int len, int pid)
{
	int i;

	i = 18;
	printf("--CLIENT: send length--\n");
	printf("length in dec: %d ... in binary: ", len);
	while (--i >= 0)
	{
		
		if ((len >> i & 1) == 0)
		{
			printf("%d", (len >> i & 1));
			kill(pid, SIGUSR1);
		}
		else
		{
			printf("%d", (len >> i & 1));
			kill(pid, SIGUSR2);
		}
		usleep(SLEEP_TIME + 10);
		// printf("%d", (len >> i & 1));
	}
	printf("\n--END OF SEND LENGTH--\n\n");
}

void send_char(char c, int pid)
{
	int i;

	printf("--CLIENT: send char--\n");
	printf("char in bits: %c ... ", c);


	i = 8;
	while (--i >= 0)
	{
		if ((c >> i & 1) == 0)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(SLEEP_TIME  + 10);
		printf("%d", c >> i & 1);
	}
	printf("\n--END OF CLIENT: send char--\n\n");
}

int	main(int ac, char **av)
{
	int	i;

	printf("--START OF MAIN--\n");
	
	if (ac != 3)
		return (1);
	if (ft_atoi(av[1]) < 0)
		return (1);
	pid_t	receiver_pid = atoi(av[1]);

	int len;
	len = ft_strlen(av[2]);
	send_length(len, receiver_pid);
	i = 0;
	while (av[2][i])
	{
		printf("-- Call send_in_bits func --\n");
		send_char(av[2][i], receiver_pid);
		i++;
	}
	printf("---END OF MAIN--\n");
	return (0);
}