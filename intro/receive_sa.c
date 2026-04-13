#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void my_handler(int signum)
{
	printf("Signal received: %d\n", signum);
}

int main(void)
{
	struct sigaction sa;

	sa.sa_handler = my_handler;
	sigemptyset(&sa.sa_mask);

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	printf("PID: %d\n", getpid());

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(1);
	else if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(1);

	while (1)
	{
	}
	return (0);
}