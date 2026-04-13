#include <signal.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t	receiver_pid = atoi(argv[1]);
	kill(receiver_pid, SIGUSR1);
	return (0);
}

