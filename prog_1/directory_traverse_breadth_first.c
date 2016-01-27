#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_Q_LENGTH 999999

/* element is copied into new memory*/
void enqueue(char** queue, int* head, int* tail, char* element)
{
	queue[*tail] = element; // enqueue
	*tail = (*tail+1) % MAX_Q_LENGTH;

	if(*tail == *head)
	{
		printf("ERROR: queue length exceeded!\n");
		exit(1);
	} // if queue is full
} // enqueue()



void dequeue(char** queue, int* head, int* tail, char** element)
{
	if(*head == *tail) // empty queue
		*element = 0;
	else
	{
		*element = queue[*head];
		queue[*head] = NULL;
		*head = (*head+1) % MAX_Q_LENGTH;
	} // pop the queue
} // dequeue()



void directory_dfs(char* start_path, char* target)
{
	char* queue[MAX_Q_LENGTH] = {0};
	int head=0;
	int tail=0;

	struct dirent *d;
	DIR *dp;

	char* popped = NULL;
	int found = 0;
	int is_root = 0;

	int i;

	if(!strcmp(start_path, "/")) // if is root case
		is_root = 1;
	else // else not root
	{
		for(i=0; start_path[i] != '\0'; i++) // find terminating 0
			;
		if(start_path[i-1] == '/')
			start_path[i-1] = '\0'; // if not root, remove forward slash
	} // else


	if((dp=opendir(start_path)) == NULL)
	{
		printf("'%s': No such location\n", start_path);
		return;
	} // if can't open start path
	else
		closedir(dp);

	popped = (char*) malloc(strlen(start_path) + 1);
	strcpy(popped, start_path);
	enqueue(queue, &head, &tail, popped); // initialize DFS
	popped = NULL;

	while(head != tail)
	{
		dequeue(queue, &head, &tail, &popped);
		puts(popped); // print pathname
		
		if((dp=opendir(popped)))
		{
			while( (d = readdir(dp)) ) // for all children in popped directory, enqueue
			{
				if(d->d_ino != 0 &&
					strcmp("..", d->d_name) != 0 &&
					strcmp(".", d->d_name) != 0)
				{
					// length is (popped + slash + d_name + \0)
					char* tmp = (char*) malloc(strlen(popped) + strlen(d->d_name) + 2);
					strcpy(tmp, popped);
					if(!is_root)
						strcat(tmp, "/");
					strcat(tmp, d->d_name); // append name to path
					enqueue(queue, &head, &tail, tmp); // enqueue child

					if(d->d_type != DT_DIR && !strcmp(d->d_name, target)) // count match
						found++;
				} // if inode is ok, not ".", and not ".."
			} // while all children

			is_root = 0;
			closedir(dp);
		} // if opened dir


		if(popped != NULL)
			free(popped);
		else
		{
			printf("ERROR: free error");
			exit(1);
		} // free error
	} // while queue is not empty

	if(found > 0)
		printf("'%s': %d matches\n", target, found);
	else
		printf("'%s': No such file\n", target);
} // directory_dfs()



const char usage_str[] = "Usage: Path to print. Defaults to PWD\n";

int main(int argc, char** argv)
{
	if(argc == 3) // two arguments
		directory_dfs(argv[1], argv[2]);
	else // else error
		printf(usage_str);

	return 0;
} // main()
