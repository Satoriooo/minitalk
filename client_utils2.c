/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:27:36 by shirose           #+#    #+#             */
/*   Updated: 2026/04/22 13:29:43 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	error_handler(char *msg)
{
	print_error(msg);
	exit(1);
}

void	safe_kill(int pid, int signum)
{
	if (kill(pid, signum) == -1)
		error_handler("Kill function failed. Check PID.");
}
