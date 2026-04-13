/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:11:20 by shirose           #+#    #+#             */
/*   Updated: 2026/04/13 15:35:29 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char bits_to_char(int signum, int n)
{
	printf("--START OF BIT_TO_CHAR--\n");
	printf("n: %d, signum: %d\n", n, signum);
	static char c = 0;

	if (n == 7)
	{	
		c = 0;
		printf("Reset c: (int) %d\n", c);
	}
	c = c | signum << n;

	return (c);
}

void my_handler(int signum)
{
	static int call = 0;
	call++;
	printf("\n--START OF MY_HANDLER: call = %d --\n", call);

	static int	strlen = 0;
	static int	tmp_strlen = 0;
	static int	cnt_digits = 0;
	static char *str;

	if (signum == SIGUSR1)
		signum = 0;
	else
		signum = 1;
	// Receive the length of the string (MAX == 2 ^ 17)
	printf("strlen: %d, cnt_digits: %d\n", strlen, cnt_digits);
	if (strlen == 0 && cnt_digits != 18)
	{
		tmp_strlen = tmp_strlen << 1;
		tmp_strlen = tmp_strlen | signum;
		cnt_digits++;
		printf("check 00: cnt_digits = %d\n", cnt_digits);
		printf("tmp_strlen: %d, signum: %d\n", tmp_strlen, signum);
		return ;
	}
	else if (strlen == 0 && cnt_digits == 18)
	{
		strlen = tmp_strlen;
		printf("strlen: %d\n", strlen);
		tmp_strlen = 0;
		
		if (!str)
			str = malloc(sizeof(char) * strlen + 1);
		if (!str)
			exit(1) ;
	}
	// Create a string with length of strlen.
	// For each character, it receives 8 bits and repeat it for (strlen) times.

	static int i = 0;
	static int idx = 0;

	printf("--CALLING BITS_TO_CHAR--\n");
	if (idx != 8 && i != strlen)
	{
		str[i] = (bits_to_char(signum, 7 - idx++));
		if (idx == 8)
			{
				i++;
				idx = 0;
			}
		if (i == strlen)
		{
			str[i] = '\0';
			printf("---RESULT: %s---\n", str);
			printf("--END OF MY_HANDLER--\n");
		}
		return ;
	}
	else if (idx == 8 && i != strlen)
	{
		printf("\n*** str[%d]: %c ***\n\n", i, str[i]);
		idx = 0;
		i++;
		str[i] = (bits_to_char(signum, 7 - idx++));
		printf("Returning 02... i: %d\n", i);
		return ;
	}
	else if (i == strlen)
	printf("%s", str);
	
	printf("--END OF MY_HANDLER--\n");
	free(str);
	exit(0) ;
}

int main(int ac, char **av)
{
	struct sigaction sa;

	sa.sa_handler = my_handler;
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return 1;
	}

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	printf("PID: %d\n", getpid());
	while (1)
	{
		usleep(SLEEP_TIME);
	}
	return (0);
}