/* Problem 4: process_tree */
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>



void print_identify(int process_num)
{
	printf("I am process %d; my process pid is %d; my parent's pid is %d.\n",
		process_num, (int)getpid(), (int)getppid());
} // print_identify()



void print_catching(int parent_num, int child_num)
{
	printf("\tParent process %d buried child %d.\n", parent_num, child_num);
} // print_catching()



void split(int depth, int parent_num)
{
	if(depth == 1)
		return;
	else // depth not 1
	{
		pid_t pid1, pid2;
		int num1 = parent_num * 2; // left fork
		int num2 = num1 + 1; // right fork

		if((pid1 = fork()) == 0)
		{
			print_identify(num1);
			split(depth - 1, num1);
		} // if this is child 1
		else // else not child 1
			if((pid2 = fork()) == 0)
			{
				print_identify(num2);
				split(depth - 1, num2);
			} // if this is child 2
			else // else parent
				if(pid1 && pid2 > 0)
				{
					waitpid(pid1, NULL, 0); // wait for child 1
					print_catching(parent_num, num1);
					waitpid(pid2, NULL, 0); // wait for child 2
					print_catching(parent_num, num2);
				} // else parent
				else // negative PID: one of the children failed to fork
				{
					printf("Failure to fork from process %d\n", parent_num);
					exit(1);
				} // else failed fork
	} // else if depth is not 1
} // split()



const char usage_str[] =
	"Usage: Single integer argument n to print process tree of depth n.\n"
	"\t Try not to go above 10\n";

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf(usage_str);
		return 1;
	} // if not given 1 argument

	for(int i=0; argv[1][i] != '\0'; i++) // check if digits are valid
		if(argv[1][i] < '0' || argv[1][i] > '9')
		{
			printf(usage_str);
			return 1;
		} // if not not a digit

	int depth = atoi(argv[1]); // get depth

	if(depth == 0) // nothing to do (root process is already depth 1)
		return 1;

	int root_process = 1; // root is process 1
	print_identify(root_process);
	split(depth, root_process); // begin tree	

	return 0;
} // main()
