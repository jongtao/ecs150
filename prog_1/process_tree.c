#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>


void identify(int num)
{
	printf("I am process %d; my process pid is %d\n", num, (int)getpid());
	printf("My parent's pid is %d\n", (int)getppid());
} // identify()



void split(int depth, int parent_num)
{
	if(depth == 1)
	{
		return;
	}
	else
	{
		pid_t pid1, pid2;
		int num1 = parent_num * 2; // left fork
		int num2 = (parent_num * 2) + 1; // right fork

		if((pid1 = fork()) == 0)
		{
			identify(num1);
			split(depth - 1, num1);
		} // if this is child 1
		else // else not child 1
			if((pid2 = fork()) == 0)
			{
				identify(num2);
				split(depth - 1, num2);
			} // if this is child 2
			else
			{
				waitpid(pid1, NULL, 0); // wait for first child
				printf("\tParent %d caught child %d\n", parent_num, num1);
				waitpid(pid2, NULL, 0); // wait for second child
				printf("\tParent %d caught child %d\n", parent_num, num2);
			} // else parent
	} // else if depth is not 1


} // split()




const char usage_str[] =
	"Usage: Single integer argument n to print process tree of depth n.\n";




int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf(usage_str);
		exit(1);
	} // if not two arguments

	// check digits
	int i;
	for(i=0; argv[1][i] != '\0'; i++)
	{
		if(argv[1][i] < '0' || argv[1][i] > '9')
		{
			printf(usage_str);
			exit(1);
		} // if not not a digit
	} // for all digits

	// get depth
	int depth = atoi(argv[1]);

	// nothing to do (origin process is already depth 1)
	if(depth == 0)
		return 0;

	// begin tree	
	identify(1);
	split(depth, 1);

	return 0;
} // main()
