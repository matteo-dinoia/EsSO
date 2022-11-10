#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include <limits.h>

#define true 1
#define false 0

/*PROTOTYPE*/
void handler_custom(int);
void exit_everything(const char *);

/*GLOBAL*/
int child_num, child_alive=0;
int *child;
int ppid, c;
int stop=true;

int main(int argc, char **argv)
{
	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3){
		dprintf(1, "ERROR: not enougth parameters\n");
		return 1;
	}
	srand(time(0));
	child_num = atoi(argv[1]);
	int module=atoi(argv[2]);
	if(child_num<=0 || module<=0){
		dprintf(1, "ERROR: negative or null parameter/s\n");
		return 1;
	}

	/*GLOBAL VARIABLE*/
	ppid = getpid();
	child=calloc(child_num, sizeof(*child));

	/*MASK FOR HANDLER*/
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGSTOP);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);

	/*SET HANDLER*/
	struct sigaction sighandler;
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler_custom;
	sighandler.sa_mask=set;
	sigaction(SIGUSR1, &sighandler, NULL);
	sigaction(SIGUSR2, &sighandler, NULL);

	/*FORK*/
	int pid;
	for (int i = 0; i < child_num; i++){
		if((pid = fork())==-1) exit_everything("ERROR: creating child");  /*error*/
		else if(pid==0) break;  /*son*/
		else{/*father*/
			child[child_alive++] = pid;
			dprintf(1, "INFO: forked %d-child (PID=%d)\n", child_alive+1, pid);
		}
	}

	/*SYNCRONIZATION*/
	if(getpid()==ppid){
		dprintf(1, "INFO: starting son wakeup\n");
		for(int i=0; i<child_num; i++)
			kill(child[i], SIGUSR2);
		dprintf(1, "INFO: finished son wakeup\n");
	}
	else{
		while(stop) pause();
	}


	/*LOOPS*/
	for (c = 0; ; c = (c + 1) % module)
		if(getpid()!=ppid && c==0 && getppid()==ppid) /*son to send to parent (still alive)*/
			kill(getppid(),  SIGUSR1);

	return 2;
}

/*HANDLER*/
void handler_custom(int signum)
{
	//dprintf(1, "Received signal %d\n", signum);
	if (signum == SIGUSR1 && getpid()==ppid){ /*FATHER RECEIVE SIGNAL*/
		/*CHECK IF c==0*/
		//if(c!=0) return;

		/*DECIDE WHICH TO KILL*/
		int to_kill=rand()%child_alive;
		int pid_to_kill=child[to_kill];

		/*REORGANIZE DATA STRUCTURE*/
		child[to_kill]=child[--child_alive]; /*put last in place of killed*/

		/*KILL CHILD*/
		dprintf(1, "KILL (alive %d /%d): n=%d PID=%d\n", child_alive, child_num, to_kill, pid_to_kill);
		kill(pid_to_kill, SIGKILL);
		waitpid(pid_to_kill, NULL, 0);
		dprintf(1, "\tFinished waiting\n");

		/*CHECK FOR CLOSING CONDITION*/
		if(child_alive<=0) exit_everything("FINISHED");
	}
	else if(signum == SIGUSR2 && getpid()!=ppid){ /*CHILD CONT*/
		dprintf(1, "Wake UP PID=%d\n", getpid());
		stop=false;
	}
}

void exit_everything(const char * exit_msg)
{
	dprintf(1, "%s\n", exit_msg);

	for (int i = 0; i < child_alive; i++)
		kill(child[i], SIGTERM);
	while(wait(NULL)!=-1);
	exit(1);
}