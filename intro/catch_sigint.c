#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	my_handler(int signum)
{
	printf("Caught signal %d! Cleaning up...\n", signum);
}

int main() {
	struct sigaction sa;

	sa.sa_handler = my_handler;

	sigemptyset(&sa.sa_mask);

	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return 1;
	}

	printf("Waiting for Ctr + C ...\n");

	while(1){
		sleep(1);
	}

	return (0);
}