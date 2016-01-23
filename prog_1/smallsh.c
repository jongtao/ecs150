#include "smallsh.h" /* include file for example */
#include <stdlib.h>


static struct sigaction act_int = {0};
static struct sigaction act_chld = {0};
static struct sigaction oact = {0};
static sigset_t mask;

static int is_int = 0;
static int fg_count = 0;
static int fg_pid = 0;



void sigint_handler(int signo)
{
	is_int = 1;
	char c,d;
	
	if(fg_count > 0)
	{
		printf("Are you sure you want to kill the child %d? (Y) ", fg_pid);
		fflush(stdout);
		c = getchar();
		while(getchar() != '\n')
			;
		if(c == 'Y')
		{
			kill(fg_pid, SIGTERM);
			is_int = 0;
			fg_count = 0;
		}
	}

} // sigint_handler



/* program buffers and work pointers */
static char inpbuf[MAXBUF], tokbuf[2*MAXBUF], *ptr = inpbuf, *tok = tokbuf;

userin(p) /* print prompt and read a line */
char *p;
{
  int c, count;
  /* initialization for later routines */
  ptr = inpbuf;
  tok = tokbuf;

  /* display prompt */
  printf("%s ", p);

	is_int = 0;
  for(count = 0;;){
    if((c = getchar()) == EOF)
		{
			if(is_int)
			{
				printf("\n");
				c = '\n';
				is_int = 0;
			}
			else
      	return(EOF);
		}
    if(count < MAXBUF)
      inpbuf[count++] = c;

    if(c == '\n' && count < MAXBUF){
      inpbuf[count] = '\0';
      return(count);
    }

    /* if line too long restart */
    if(c == '\n'){
      printf("smallsh: input line too long\n");
      count = 0;
      printf("%s ", p);
    }
  }
}

static char special[] = {' ', '\t', '&', ';', '\n', '\0'};

inarg(c) /* are we in an ordinary argument */
char c;
{
  char *wrk;
  for(wrk = special; *wrk != '\0'; wrk++)
    if(c == *wrk)
      return(0);

  return(1);
}

gettok(outptr) /* get token and place into tokbuf */
char **outptr;
{
  int type;

  *outptr = tok;

  /* strip white space */
  for(;*ptr == ' ' || *ptr == '\t'; ptr++)
    ;

  *tok++ = *ptr;

  switch(*ptr++){
    case '\n':
      type = EOL; break;
    case '&':
      type = AMPERSAND; break;
    case ';':
      type = SEMICOLON; break;
    default:
      type = ARG;
      while(inarg(*ptr))
        *tok++ = *ptr++;
  }

  *tok++ = '\0';
  return(type);
}

/* execute a command with optional wait */
runcommand(cline, where)
char **cline;
int where;
{
  int pid, exitstat, ret;

  if((pid = fork()) < 0){
    perror("smallsh");
    return(-1);
  }

  if(pid == 0){
		sigemptyset(&mask);
		sigaddset(&mask, SIGINT);
		sigprocmask(SIG_BLOCK, &mask, NULL);

    execvp(*cline, cline);
    perror(*cline);
    exit(127);
  }

  /* code for parent */
  /* if background process print pid and exit */
  if(where == BACKGROUND){
    printf("[Process id %d]\n", pid);
    return(0);
  }
	else
	{
		fg_count++;
		fg_pid = pid;
	}

wait_more:
  /* wait until process pid exits */
  while( (ret=wait(&exitstat)) != pid && ret != -1)
    ;

	if(is_int)
	{
		is_int = 0;
		goto wait_more;
	}

	fg_count = 0;
  return(ret == -1 ? -1 : exitstat);
}

procline() /* process input line */
{
  char *arg[MAXARG+1]; /* pointer array for runcommand */
  int toktype; /* type of token in command */
  int narg; /* numer of arguments so far */
  int type; /* FOREGROUND or BACKGROUND? */

  for(narg = 0;;){ /* loop forever */
    /* take action according to token type */
    switch(toktype = gettok(&arg[narg])){
      case ARG:
        if(narg < MAXARG)
          narg++;
        break;

      case EOL:
      case SEMICOLON:
      case AMPERSAND:
        type = (toktype == AMPERSAND) ? BACKGROUND : FOREGROUND;

        if(narg != 0){
          arg[narg] = NULL;
          runcommand(arg, type);
        }
        
        if(toktype == EOL)
          return;

        narg = 0;
        break;
    }
  }
}

char *prompt = "Command>"; /* prompt */

main()
{

	act_int.sa_handler = sigint_handler;
	sigemptyset(&act_int.sa_mask);
	sigaddset(&act_int.sa_mask, SIGINT);
	sigaction(SIGINT, &act_int, 0);

  while(userin(prompt) != EOF)
    procline();
}

