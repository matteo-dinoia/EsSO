#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define PANIC_NUM(string, num) exit((dprintf(1, "FATAL (line: %d): %s [%d]\n", __LINE__, (string), (num)), 1))
#define PANIC(string) exit((dprintf(1, "FATAL (line: %d): %s\n", __LINE__, (string)), 1))

void custom_handler(int);
int num_alive, *child;

int main(int argc, char **argv){
	/*DECLARATION*/
	struct sigaction handler;
	int i, t, num_child, pid;
	int status, statuses_sum, counter, str_max=num_child;
	char *str_statuses;
	char *const arg[]={"char-loop", "Hello", NULL};
	char *const env[]={NULL};

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<2)
		PANIC("not enougth parameters");
	num_child=atoi(argv[1]);
	if(num_child<=0)
		PANIC("negative or null parameter/s");

	/*SET SIGACTION*/
	bzero(&handler, sizeof(handler));
	handler.sa_handler=&custom_handler;
	sigaction(SIGALRM, &handler, NULL);

	/*CREATE CHILD*/
	pid;
	child=calloc(num_child, sizeof(*child));
	for(i=0; i<num_child; i++){
		if((pid=fork())==0){/*CHILD*/
			free(child);
			execve("char-loop", arg, env);
			/*if execve return it mean it failed*/
			PANIC("executing execve");
		}
		else if(pid==-1)
			PANIC("during forking child");
		child[i]=pid;
	}

	/*START ALARM*/
	srand(time(0)*getpid());
	num_alive=num_child;
	alarm(1);

	/*GET SIGNAL*/
	statuses_sum=0;
	counter=0;
	str_statuses=calloc(num_child+1, sizeof(*str_statuses)); /*create string of statuses setted to 0*/
	while(wait(&status)!=-1 || errno==EINTR){
		if(errno==EINTR){/*wait failed*/
			errno=EXIT_SUCCESS;
			continue;
		}

		/*PRINT RETURN STATUS*/
		t=WEXITSTATUS(status);
		statuses_sum=(statuses_sum+t)%256;
		if(t==0){ /*Avoiding string closure*/
			dprintf(1, "CHILD TERMINATED with status 0\n");
			continue;
		}
		else{
			if(counter>=str_max){
				str_max=str_max*2;
				str_statuses=realloc(str_statuses, str_max);
				if (str_statuses == NULL)  /*your realloc didn't work*/
					PANIC("error during realloc");

			}
			str_statuses[counter++]=(char) t;
			str_statuses[counter]='\0';
			dprintf(1, "CHILD %d TERMINATED with status: %d '%c', sum is: %d string of return statuses:\n\t %s\n", counter, t, t, statuses_sum, str_statuses);
		}

		/*EXIST STATUS*/
		if(statuses_sum==0) /*exit condition*/
			break;

		/*CREATE NEW SON*/
		if((pid=fork())==0){/*CHILD*/
			execve("char-loop", arg, env);
			/*if execve return it mean it failed*/
			PANIC("executing execve");
		}
		else if(pid==-1)
			PANIC("during forking child");
		child[num_alive++]=pid;

		/*SET ALARM*/
		alarm(1);
	}

	/*KILLING AND CLOSING ALL PROCESS*/
	for(i=0; i<num_alive; i++)
		kill(child[i], SIGINT);
	while(wait(&status)!=-1){}

	/*FREE*/
	free(child);
	free(str_statuses);

	return 0;
}

void custom_handler(int signal){
	/*DECLARATION*/
	int to_kill, pid_to_kill;

	if(signal!=SIGALRM)
		return;

	/*DECIDE WHICH TO KILL*/
	to_kill=rand()%num_alive;
	pid_to_kill=child[to_kill];

	/*REORGANIZE DATA STRUCTURE*/
	child[to_kill]=child[--num_alive]; /*put last in place of killed*/

	/*KILL CHILD*/
	kill(pid_to_kill, SIGINT);

}