/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:21:22 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 19:21:22 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

size_t	ft_strlen(char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	print_error(char *s)
{
	if (s)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
	}
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
	if (nb > 2147483647)
		return (-1);
	return (nb * sign);
}

int	is_int(char *s)
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
