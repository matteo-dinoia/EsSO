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
void child_loop(int);
void parent_loop(int, int *, int);

/*GLOBAL*/
long num_to_kill = 0; /*Right to edit only to handler*/

int main(int argc, char **argv)
{

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3){
		dprintf(1, "ERROR: not enougth parameters\n");
		return 1;
	}
	srand(time(0));
	int child_num = atoi(argv[1]);
	int module=atoi(argv[2]);
	if(child_num<=0 || module<=0){
		dprintf(1,"ERROR: negative or null parameter/s\n");
		return 1;
	}

	/*SET HANDLER*/
	struct sigaction sighandler;
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler_custom;
	sigaction(SIGUSR1, &sighandler, NULL);

	/*FORK*/
	int pid, child_pid[child_num];
	for (int i = 0; i < child_num; i++){
		pid = fork();
		dprintf(1,"INFO: forking %d-child\n", i);

		if(pid<0){
			dprintf(1,"ERROR: creating child\n");
			for (int i2 = 0; i2 < i; i2++)
				kill(child_pid[i2], SIGTERM);
			while(wait(NULL)!=-1){};
			return 1;
		}
		else if(pid==0) break;
		else child_pid[i] = pid;
	}

	/*LOOPS*/
	if(pid==0) child_loop(module);
	else parent_loop(module, child_pid, child_num);
	return 2;
}

/*LOOPS*/
void child_loop(int module)
{
	for (int i = 0; ; i = (i + 1) % module){
		if(i==0){
			kill(getppid(), SIGUSR1);
			//sleep(1);        //-> for more efficency
			//dprintf(1,"CALL PARENT: PID=%d\n", getpid());
		}
	}
}
void parent_loop(int module, int *child_pid, int child_num)
{
	int child_alive = child_num, rng;
	for (int i = 0;; i = (i + 1) % module){

		/*IF THERE IS NEED TO KILL*/
		while(child_num-child_alive < num_to_kill){
			/*RANDOM NUMBER */
			while(child_pid[rng = rand() % child_num]==0); /*not yet used*/

			/*KILL*/
			dprintf(1,"KILL (alive %d, tokill %d): n=%d PID=%d\n", child_alive, num_to_kill, rng, child_pid[rng]);
			kill(child_pid[rng], SIGTERM);
			child_pid[rng] = 0;

			/*CHECK FOR CLOSING CONDITION*/
			child_alive--;
			if(child_alive<=0){
				dprintf(1,"Finished\n");
				while(wait(NULL)!=-1){};
				exit(0);
			}

		}
	}
}

/*HANDLER*/
void handler_custom(int signum)
{
	if(signum==SIGUSR1){
		if(num_to_kill<LONG_MAX)
			num_to_kill++;
	}
}