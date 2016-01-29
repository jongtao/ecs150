#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
	//Holds the user's input (AAJ)
	char input[500] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ";

	//Holds the input in a new variable for process 2 (AAJ)
	char inputbuffer[500] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ";

	//Holds the input in a new variable for process 3 (AAJ)
	char inputbuffer2[500] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ";

	//Holds the input in a new variable for process 1 (AAJ)
	char inputbuffer3[500] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ";

	//Holds the length of the input (AAJ)
	int inputLength = 0;

	//A temporary variable for holding the inverted input int process 2 (AAJ)
	char tempinputbuffer[500] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ";

	//A temporary counter for copying the input in process 2 (AAJ)
	int count = 0;

	//Hold the pid's for the processes (AAJ)
	pid_t process0pid;
	pid_t process1pid;
	pid_t process2pid;
	pid_t process3pid;

	//Hold the file destinations for the pipes (AAJ)
	//Process 0 to Process 3 (AAJ)
	int p0[2];
	//Process 1 to Process 2 (AAJ)
	int p1[2];
	//Process 2 to Process 3 (AAJ)
	int p2[2];

	//Gets the pid of the original process (AAJ)
	process0pid = getpid();

	//Opens a pipe and checks for errors (AAJ)
	if(pipe(p0) == -1)
	{
		perror("pipe call");
		exit(1);
	}//if
	
	//Creates a child process to complete process 1 (AAJ)
	process1pid = fork();

	//Runs process one if it is the child process (AAJ)
	if(process1pid == 0)
	{
		//Prints the canned message for process 1 (AAJ)
		printf("I am process P1\n");
		printf("My pid is p%d\n", getpid());
		printf("Please enter a string: ");

		//Gets the user's input (AAJ)
		scanf("%[^\n]", &input);
		
		//Gets the length of the input (AAJ)
		for(int i = 0; i < 501; i++)
		{
			if(input[i] != '\0')
			{
				inputLength++;
			}//if
			else
			{
				//Stops counting characters when the terminating null is reached (AAJ)
				break;			
			}//else
		}//for

		//Opens a pipe and checks for errors (AAJ)
		if(pipe(p1) == -1)
		{
			perror("pipe call");
			exit(1);
		}//if

		//Writes down the pipe from process 1 to process 2 (AAJ)
		write(p1[1], input, inputLength);

		//Creates a child process to complete process 2 (AAJ)
		process2pid = fork();

		//Runs process two if it is the child process (AAJ)
		if(process2pid == 0)
		{
			//Starts printing the canned message for process 2 (AAJ)
			printf("\nI am process P2\n");
			printf("My pid is p%d\n", getpid());
			printf("I just received the string ");
			
			//Gets the input from the pipe from process 1 (AAJ)
			read(p1[0], inputbuffer, inputLength);
			
			//Prints the input (AAJ)
			for(int i = 0; i < inputLength; i++)
			{
				if(inputbuffer[i] != '\0')
				{
					printf("%c", inputbuffer[i]);
				}//if
				else
				{
					//Stops printing characters when the terminating null is reached (AAJ)
					break;			
				}//else
			}//for

			//Continues the canned message for process 2 (AAJ)
			printf("\nI am sending ");

			//Prints the inverted input (AAJ)
			for(int i = inputLength - 1; i >= 0; i--)
			{
				printf("%c", inputbuffer[i]);

				//Puts the reversed message in the buffer variable to be passed onto process 3 (AAJ)
				tempinputbuffer[count] = inputbuffer[i];

				//Increments count (AAJ)
				++count;
			}//for

			//Finishes the canned message for process 2 (AAJ)
			printf(" to P3\n\n");
			
			//Opens a pipe and checks for errors (AAJ)
			if(pipe(p2) == -1)
			{
				perror("pipe call");
				exit(1);
			}//if
			
			//Writes down the pipe from process 2 to process 3 (AAJ)
			write(p2[1], tempinputbuffer, inputLength);

			//Creates a child process to complete process 3 (AAJ)
			process3pid = fork();

			//Runs process three if it is the child process (AAJ)
			if(process3pid == 0)
			{
				
				//Starts printing the canned message for process 3 (AAJ)
				printf("I am process P3\n");
				printf("My pid is p%d\n", getpid());
				printf("I just received the string ");

				//Gets the input from the pipe from process 3 (AAJ)
				read(p2[0], inputbuffer2, inputLength);
				
				//Prints the input (AAJ)
				for(int i = 0; i < inputLength; i++)
				{
					if(inputbuffer2[i] != '\0')
					{
						printf("%c", inputbuffer2[i]);
					}//if
					else
					{
						//Stops printing characters when the terminating null is reached (AAJ)
						break;			
					}//else
				}//for

				//Continues the canned message for process 3 (AAJ)
				printf("\nI am sending ");

				//Capitilizes the input (AAJ)
				for(int i = 0; i < inputLength; i++)
				{
					if(inputbuffer2[i] >= 97 && inputbuffer2[i] <= 122)
					{
						//Changes the lower case letter to upper case letters by
						//decrease the characters decimal value (AAJ)
						inputbuffer2[i] -= 32;

						printf("%c", inputbuffer2[i]);

					}//if
					else
					{
						printf("%c", inputbuffer2[i]);
					}//else
				}//for

				//Finishes the canned message for process 3 (AAJ)
				printf(" to P1\n\n");
				
				//Writes down the pipe from process 3 to process 0 (AAJ)
				write(p0[1], inputbuffer2, inputLength);

			}//if
			else
			{
				wait();

				//Starts printing the canned message for killing process 3 (AAJ)
				printf("I am process P3\n");
				printf("My pid is p%d\n", process3pid);
				printf("I am about to die\n\n");
				
				//Kills this process (AAJ)
				kill(process3pid, SIGEV_NONE);

			}//else
		}//if
		else
		{
			//Gets the input from the pipe from process 3 (AAJ)
			read(p0[0], inputbuffer3, inputLength);

			//Starts printing the canned message for process 0 (AAJ)
			printf("I am process P1\n");
			printf("My pid is p%d\n", getpid());
			printf("I just received the string ");

			//Prints the input (AAJ)
			for(int i = 0; i < inputLength; i++)
			{
				if(inputbuffer3[i] != '\0')
				{
					printf("%c", inputbuffer3[i]);
				}//if
				else
				{
					//Stops printing characters when the terminating null is reached (AAJ)
					break;			
				}//else
			}//for

			//Prints two new lines (AAJ)
			printf("\n\n");

			//Waits to kill process 2 until process 1 finisheds (AAJ)
			wait();

			//Starts printing the canned message for killing process 2 (AAJ)
			printf("I am process P2\n");
			printf("My pid is p%d\n", process2pid);
			printf("I am about to die\n\n");
			
			//Kills this process (AAJ)
			kill(process2pid, SIGEV_NONE);

		}//else
	}//if
	else
	{
		//This wait is needed for the scanf() (AAJ)
		wait();
		
		//Starts printing the canned message for killing process 1 (AAJ)
		printf("I am process P1\n");
		printf("My pid is p%d\n", process1pid);
		printf("I am about to die\n\n");
		
		//Kills this process (AAJ)
		kill(process1pid, SIGEV_NONE);
		
	}//else
	
	return (0);
}