#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 99


void sigusr1_handler(int signo){} // does nothing


void up_string(char* string)
{
	for(int i = 0; string[i] != 0; i++)
		string[i] = toupper(string[i]);
} // up_string()


void reverse_string(char* string)
{
	int i = 0;
	int j = strlen(string) - 1;
	char tmp;

	while(i <= j)
	{
		tmp = string[j];
		string[j] = string[i];
		string[i] = tmp;
		i++;
		j--;
	}
} // reverse_string()


int main(void)
{
	struct sigaction act = {0};	
	act.sa_handler = sigusr1_handler;
	sigfillset(&act.sa_mask);
	sigaction(SIGUSR1, &act, 0);

	int pipefd[3][2];
	char buf[BSIZE];
	const char please_str[] = "Please enter a string: ";

	if(pipe(pipefd[0]) == -1)
		exit(1);

	if(pipe(pipefd[1]) == -1)
		exit(1);

	if(pipe(pipefd[2]) == -1)
		exit(1);

	if(!fork())
	{
		printf("\nI am process P1 with PID %d.\n", getpid());
		write(1, please_str, strlen(please_str));
		scanf("%s", buf);
		write(pipefd[1][1], buf, BSIZE);

		read(pipefd[0][0], buf, BSIZE);
		printf("\nI am process P1 with PID %d.\n", getpid());
		printf("I received: '%s'\n", buf);
		printf("\nI am process P1 with PID %d.\n"
			"I am about to die\n", getpid());
		kill(0, SIGUSR1);	
	} // process 1
	else
		if(!fork())
		{
			read(pipefd[1][0], buf, BSIZE);
			printf("\nI am process P2 with PID %d.\n", getpid());
			printf("I just received '%s'\n", buf);
			reverse_string(buf);
			printf("I am sending '%s' to P3\n", buf);
			write(pipefd[2][1], buf, BSIZE);

			pause();
			printf("\nI am process P2 with PID %d.\n"
				"I am about to die\n", getpid());
		} // process 2
		else
			if(!fork())
			{
				read(pipefd[2][0], buf, BSIZE);
				printf("\nI am process P3 with PID %d.\n", getpid());
				printf("I just received '%s'\n", buf);
				up_string(buf);
				printf("I am sending '%s' to P1\n", buf);
				write(pipefd[0][1], buf, BSIZE);

				pause();
				printf("\nI am process P3 with PID %d.\n"
					"I am about to die\n", getpid());
			} // process 3
			else
			{
				wait(NULL);
				wait(NULL);
				wait(NULL);
			} // origin process

	return 0;
} // main()
