/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:15:52 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 19:15:52 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static volatile sig_atomic_t	g_state = 0;

static void	signal_confirmation(int signum, siginfo_t *si, void *context)
{
	static int n = 0;
	printf("signal_confirmation ... n:%d\n", n++);
	(void)si;
	(void)context;
	if (signum == SIGUSR1)
		g_state = 0;
	if (signum == SIGUSR2)
		g_state = 1;
}

static void	error_handler(char *msg)
{
	print_error(msg);
	exit(1);
}

static void	safe_kill(int pid, int signum)
{
	if (kill(pid, signum) == -1)
		error_handler("Kill function failed. Check PID.");
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
		while (g_state == 1)
		{
			usleep(100);
			cnt++;
			if (cnt == 5000)
				error_handler("Time out: Can't receive confirmation.");
		}
	}
}

void	send_length(char *s, int pid)
{
	size_t	i = 0;
	size_t	cnt;
	size_t	len;

	len = ft_strlen(s) + 1;
	while (i < 64)
	{
		g_state = 1;
		if ((len >> (63 - i++) & 1) == 0)
			safe_kill(pid, SIGUSR1);
		else
			safe_kill(pid, SIGUSR2);
		cnt = 0;
		while (g_state == 1)
		{
			usleep(100);
			cnt++;
			if (cnt == 10000)
				error_handler("Time out: Can't receive confirmation.");
		}
	}
}

static void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_confirmation;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
		error_handler("Failed to initialize signal set.");
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		error_handler("Failed to initialize sigaction.");
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	if (ac != 3)
		error_handler("Invalid number of parameters.");
	if (ft_strlen(av[1]) > 12 || is_int(av[1]) == -1 || ft_atoi(av[1]) <= 0)
		error_handler("Invalid PID.");
	pid = ft_atoi(av[1]);
	init_signals();
	send_length(av[2], pid);
	i = 0;
	while (av[2][i])
		send_char((unsigned char)av[2][i++], pid);
	send_char('\0', pid);
	ft_putstr_fd("Message successfully received.", 1);
	return (0);
}

/*
100 letters:
0000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000

300 emojis:
🥶😏🤢🤕💩😲😛🥵🦷🤢👣👎🤞😚🤑😵😥🤌🤙💀👆🙄😳🦵
😞👣🤞🦿😍😱😧🧠😜😦😝😼🤫😏🤫🥳🤝🦶🤨👻🥳😈✊👅
👌😗🤌🤝😧😧😡🤕🤯😈👹🤙😲🎃👅🩸💋👉😥💋🤔😼🤯😾
🤗😖😳🤒😺🤝😏😍✊🙂💀🤘🙌😿🤠👄💅😾🦾👌😼👀👺👀
😢😇🤮😴😘🤔🤫👽🤥✊🫀🤠🤕🤮😃😴🤬🤙👐😫🤘🙂🙀👻
👂😖🤖😶😍🤚😛😇🦴💩😡🤧🤗👌😆😧💪🦵🤓😄😕😵😤😊
😇😒🤓🫁🫀😀🤬🩸😺😺🙁😿👆😵🖕👻😵🤨🤨😍🫀👏💀👿
😘😄🥺😦😓😰👌🫁😯😚😖🤳🥺👎👽🥶👃🧐🥱👿🧐👹🤨😬
🤓🤢🤳🦿😓😹😌👇😜🤐👀😶🦶😜✋🤥👏🤞👆👽👉🤓🙁😄
👂🦶😮😊😩🤒👆😯✋🤭🤐😝👿👋🤖💀😕🧠🤫😸🤏👻✋😥
👻😯🙄🤟🥺🤭🤬😫🫀😬😲😠🙌😚🤮😋😤😡🤬👹🦵😴👇🤌
🤟💩🤓🤌😇👀🤛🥳👣😴🤠😝🖖✊😡🙌😱👿😥😍😡🙌😱👿
😥😍😡🙌😱👿😥🙌🤌🙏

*/