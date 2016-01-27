#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>



unsigned count = 0;

void sigalrm_handler(int signo)
{
	printf("Count is %u, my pid is %d\n", count, getpid());
	count = 0;
} // sigalrm_handler()



int main(void)
{
	struct sigaction act = {0};	
	act.sa_handler = sigalrm_handler;
	sigfillset(&act.sa_mask);
	sigaction(SIGALRM, &act, 0);

	pid_t pid1, pid2;

	if((pid1 = fork()) == 0)
		for(count=0;;count++);
	else
		if((pid2 = fork()) == 0)
			for(count=0;;count++);
		else // parent
		{
			for(int i=0; i<5; i++)
			{
				sleep(1);
				puts("ALRM");
				kill(pid1, SIGALRM);
				kill(pid2, SIGALRM);
			} // for loop 5 times

			sleep(1);
		} // if parent

	return 0;
} // main()
