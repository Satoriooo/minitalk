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

	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return 1;
	}
	printf("PID: %d\n", getpid());
	signal(SIGUSR1, my_handler);
	while (1)
	{
		sleep(1);
	}
	return (0);
}