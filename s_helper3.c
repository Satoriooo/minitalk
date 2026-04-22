/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_helper3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:55:20 by shirose           #+#    #+#             */
/*   Updated: 2026/04/21 19:54:52 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid <= 0)
		error_handler("Invalid PID.");
	printf("signal_handler ... \n");
	printf("	g_data.pid_occupied: %d, g_data.client_pid %d, info->si_pid: %d\n", g_data.pid_occupied, g_data.client_pid, info->si_pid);

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
	printf("g_data.bit: %d, g_data.error_state: %d\n", g_data.bit, g_data.error_state);
	printf("--END OF SIGNAL HANDLER--\n");
}