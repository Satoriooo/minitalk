/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:03:07 by shirose           #+#    #+#             */
/*   Updated: 2026/04/21 18:59:44 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

size_t	get_strlen(int i)
{
	static size_t	n;

	if (i == 0)
		n = 0;
	n = n << 1 | g_data.bit;
	return (n);
}

char	bits_to_char(int signum)
{
	static unsigned char	c = 0;

	c = c << 1 | signum;
	return (c);
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
void	loop_reset(size_t *i, size_t *idx, size_t *len)
	{
		*i = -1;
		*idx = 0;
		*len = 0;
	}

void	error_handler(char *msg)
{
	print_error(msg);
	g_data.error_state = 1;
}