#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum)
{
	printf("Received signal %d\n", signum);
}

int main(void)
{
	signal(SIGINT, handler); //SIGINTを受け取ったらhandler関数へ
	while (1)
		sleep(3);
	return (0);
}