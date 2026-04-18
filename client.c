/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:16 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 00:22:43 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	signal_confirmation(int signum, siginfo_t *si, void *context)
{
	(void)signum;
	(void)si;
	(void)context;
	g_state = 0;
}

static int	error_handler(char *msg)
{
	print_error(msg);
	exit (1);
}

static void	safe_kill(int pid, int signum)
{
    if (kill(pid, signum) == -1)
        error_handler("Kill function failed. Check server issue, invalid PID.");
}

static void	send_char(unsigned char c, int pid)
{
	int	i;
	int	cnt;

	i = 8;
	while (--i >= 0)
	{
		g_state = 1;
		if ((c >> i & 1) == 0)
			safe_kill(pid, SIGUSR1);
		else
			safe_kill(pid, SIGUSR2);
		cnt = 0;
		while(g_state == 1)
		{
			usleep(100);
			cnt++;
			if (cnt == 5000)
				error_handler("Time out: Can't receive confirmation.");
		}
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					i;
	int					pid;

	if (ac != 3)
		error_handler("Invalid number of parameters.");
	if (ft_strlen(av[1]) > 12 || is_int(av[1]) == -1 || ft_atoi(av[1]) <= 0)
		error_handler("Invalid PID.");
	pid = ft_atoi(av[1]);
	sa.sa_sigaction = &signal_confirmation;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
	|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_handler("Failed to initialize sigaction.");
	i = 0;
	while (av[2][i])
		send_char((unsigned char)av[2][i++], pid);
	send_char('\0', pid);
	return (0);
}

/*
100 letters:
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

300 emojis:
🥶😏🤢🤕💩😲😛🥵🦷🤢👣👎🤞😚🤑😵😥🤌🤙💀👆🙄😳🦵🙌🤌🙏 😞👣🤞🦿😍😱😧🧠😜😦😝😼🤫😏🤫🥳🤝🦶🤨👻🥳😈✊👅👌😗🤌🤝😧😧😡🤕🤯😈👹🤙😲🎃👅🩸💋👉😥💋🤔😼🤯😾🤗😖😳🤒😺🤝😏😍✊🙂💀🤘🙌😿🤠👄💅😾🦾👌😼👀👺👀😢😇🤮😴😘🤔🤫👽🤥✊🫀🤠🤕🤮😃😴🤬🤙👐😫🤘🙂🙀👻👂😖🤖😶😍🤚😛😇🦴💩😡🤧🤗👌😆😧💪🦵🤓😄😕😵😤😊😇😒🤓🫁🫀😀🤬🩸😺😺🙁😿👆😵🖕👻😵🤨🤨😍🫀👏💀👿😘😄🥺😦😓😰👌🫁😯😚😖🤳🥺👎👽🥶👃🧐🥱👿🧐👹🤨😬🤓🤢🤳🦿😓😹😌👇😜🤐👀😶🦶😜✋🤥👏🤞👆👽👉🤓🙁😄👂🦶😮😊😩🤒👆😯✋🤭🤐😝👿👋🤖💀😕🧠🤫😸🤏👻✋😥👻😯🙄🤟🥺🤭🤬😫🫀😬😲😠🙌😚🤮😋😤😡🤬👹🦵😴👇🤌🤟💩🤓🤌😇👀🤛🥳👣😴🤠😝🖖✊😡🙌😱👿😥😍😡🙌😱👿😥😍😡🙌😱👿😥


*/