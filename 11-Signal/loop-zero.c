#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include <limits.h>

/*PROTOTYPE*/
void handler_custom(int);

/*GLOBAL*/
int child_num, *child, child_alive;
int enabled_signal=0;
int ppid;

int main(int argc, char **argv)
{

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3){
		dprintf(1, "ERROR: not enougth parameters\n");
		return 1;
	}
	srand(time(0));
	child_alive=child_num = atoi(argv[1]);
	int module=atoi(argv[2]);
	if(child_num<=0 || module<=0){
		dprintf(1, "ERROR: negative or null parameter/s\n");
		return 1;
	}

	/*GLOBAL VARIABLE*/
	ppid = getpid();
	int child_pid[child_num];
	bzero(child_pid, sizeof(*child_pid) * child_num);
	child = child_pid;

	/*SET HANDLER*/
	struct sigaction sighandler;
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler_custom;
	sigaction(SIGUSR1, &sighandler, NULL);

	/*FORK*/
	int pid;
	for (int i = 0; i < child_num; i++)
	{
		dprintf(1, "INFO: forking %d-child\n", i);
		pid = fork();

		if(pid<0){
			dprintf(1, "ERROR: creating child\n");
			for (int i2 = 0; i2 < i; i2++)
				kill(child[i2], SIGTERM);
			while(wait(NULL)!=-1){};
			exit(1);
		}
		else if(pid==0) break;
		else child[i] = pid;
	}

	/*SYNCRONIZATION*/
	if(getpid()==ppid){
		enabled_signal=1;
		for(int i=0; i<child_num; i++)
			kill(child[i], SIGCONT);
		dprintf(1, "INFO: signal enabled\n");
	}
	else raise(SIGSTOP);

	/*LOOPS*/
	for (int i = 0; ; i = (i + 1) % module){
		if(getpid()!=ppid && i==0 && getppid()==ppid /*&& enabled_signal*/){ /*son to send to parent (still alive)*/
			kill(getppid(),  SIGUSR1);
			//dprintf(1,"CALL PARENT: PID=%d\n", getpid());
		}
	}

	return 2;
}

/*HANDLER*/
void handler_custom(int signum)
{

	if (signum == SIGUSR1){
		/*ONLYS SON
		if(ppid!=getpid()){
			enabled_signal=1;
			return;
		}*/

		/*ONLY PARENT*/
		/*RANDOM NUMBER */
		int rng, i;
		while (child[rng = rand() % child_num] == 0); /*random not yet used*/

		/*KILL*/
		dprintf(1, "KILL (alive %d /%d): n=%d PID=%d\n", child_alive, child_num, rng, child[rng]);
		kill(child[rng], SIGTERM);
		child[rng] = 0;

		/*CHECK FOR CLOSING CONDITION*/
		child_alive--;
		if(child_alive<=0){
			dprintf(1, "Finished\n");
			while(wait(NULL)!=-1){};
			exit(0);
		}
	}
}