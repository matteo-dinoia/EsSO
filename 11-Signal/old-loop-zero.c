#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <wait.h>
#include <string.h>
#include <limits.h>

#define PANIC_NUM(string, num) exit((dprintf(1, "FATAL (line: %d): %s [%d]\n", __LINE__, (string), (num)), 1))
#define PANIC(string) exit((dprintf(1, "FATAL (line: %d): %s\n", __LINE__, (string)), 1))

/*PROTOTYPE*/
void handler_custom(int);
void child_loop(int);
void parent_loop(int, int *, int);

/*GLOBAL*/
long num_to_kill = 0; /*Right to edit only to handler*/

int main(int argc, char **argv)
{
	/*DECLARATION*/
	int child_num, module, i, pid, i2;
	int *child_pid;
	struct sigaction sighandler;

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3)
		PANIC("not enougth parameters");
	srand(time(0));
	child_num = atoi(argv[1]);
	child_pid=calloc(child_num, sizeof(*child_pid));
	module=atoi(argv[2]);
	if(child_num<=0 || module<=0)
		PANIC("negative or null parameter/s");

	/*SET HANDLER*/
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler_custom;
	sigaction(SIGUSR1, &sighandler, NULL);

	/*FORK*/
	for (i = 0; i < child_num; i++){
		pid = fork();


		if(pid<0){
			dprintf(1,"ERROR: creating child\n");
			for (i2 = 0; i2 < i; i2++)
				kill(child_pid[i2], SIGTERM);
			while(wait(NULL)!=-1){};

			free(child_pid);
			return 1;
		}
		else if(pid==0){ /*SON*/
			free(child_pid);
			break;
		}
		else{/*FATHER*/
			dprintf(1,"INFO: forked %d-child\n", (i+1));
			child_pid[i] = pid;
		}
	}

	/*LOOPS*/
	if(pid==0) child_loop(module);
	else parent_loop(module, child_pid, child_num);
	return 2;
}

/*LOOPS*/
void child_loop(int module)
{
	int i;
	for (i = 0; ; i = (i + 1) % module)
		if(i==0) kill(getppid(), SIGUSR1);
}
void parent_loop(int module, int *child_pid, int child_num)
{
	/*DECLARATION*/
	int child_alive, rng, i;

	child_alive=child_num;
	for (i = 0;; i = (i + 1) % module){

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

				free(child_pid);
				exit(0);
			}

		}
	}
}

/*HANDLER*/
void handler_custom(int signum)
{
	if(signum==SIGUSR1 && num_to_kill<LONG_MAX)
		num_to_kill++;
}