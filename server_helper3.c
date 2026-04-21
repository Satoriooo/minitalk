/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:55:20 by shirose           #+#    #+#             */
/*   Updated: 2026/04/21 19:02:44 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid <= 0)
		error_handler("Invalid PID.");
	if (g_data.pid_occupied == 1 && g_data.client_pid != info->si_pid)
		return ;
	if (g_data.pid_occupied == 0)
	{
		g_data.client_pid = info->si_pid;
		g_data.pid_occupied = 1;
	}
	if (signum == SIGUSR1)
		g_data.bit = 0;
	else
		g_data.bit = 1;
	g_data.busy = 1;
}