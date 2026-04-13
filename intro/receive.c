#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum)
{
	printf("Signal received: %d\n", signum);
}

int main(void)
{
	printf("PID: %d\n", getpid());
	signal(SIGUSR1, handler);
	while (1)
	{
		pause();
	}
	return (0);
}