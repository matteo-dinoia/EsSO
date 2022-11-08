#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <errno.h>

void custom_handler(int);

int num_alive, *child;

int main(int argc, char **argv){
	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<2){
		dprintf(1, "ERROR: not enougth parameters\n");
		return 1;
	}
	int num_child=atoi(argv[1]);
	if(num_child<=0){
		dprintf(1, "ERROR: negative or null parameter/s\n");
		return 1;
	}

	/*SET SIGACTION*/
	struct sigaction handler;
	bzero(&handler, sizeof(handler));
	handler.sa_handler=&custom_handler;
	sigaction(SIGALRM, &handler, NULL);

	/*CREATE CHILD*/
	int pid;
	child=calloc(num_child, sizeof(*child));
	for(int i=0; i<num_child; i++){
		if((pid=fork())==0){/*CHILD*/
			char *const argv[]={"char-loop", "Hello", NULL};
			char *const env[]={NULL};
			execve("char-loop", argv, env);
			dprintf(1, "ERROR: executing execve\n");
			exit(2);
		}
		else if(pid==-1){
			dprintf(1, "ERROR: during forking child\n");
			exit(1);
		}
		child[i]=pid;
	}

	/*START ALARM*/
	srand(time(0)*getpid());
	num_alive=num_child;
	alarm(1);

	/*GET SIGNAL*/
	int status, statuses_sum=0, counter=0, str_max=num_child;
	char *str_statuses=calloc(num_child+1, sizeof(*str_statuses)); /*create string of statuses setted to 0*/
	while(wait(&status)!=-1 || errno==EINTR){
		if(errno==EINTR){/*wait failed*/
			errno=EXIT_SUCCESS;
			continue;
		}

		/*PRINT RETURN STATUS*/
		int t=WEXITSTATUS(status);
		statuses_sum=(statuses_sum+t)%256;
		if(t==0){ /*Avoiding string closure*/
			dprintf(1, "CHILD TERMINATED with status 0\n");
			continue;
		}
		else{
			if(counter>=str_max){
				str_max=str_max*2;
				str_statuses=realloc(str_statuses, str_max);
				if (str_statuses == NULL){  /*your realloc didn't work*/
					dprintf(1, "ERROR wih memory managment");
				}
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
			char *const argv[]={"char-loop", "Hello", NULL};
			char *const env[]={NULL};
			execve("char-loop", argv, env);
			dprintf(1, "ERROR: executing execve\n");
			exit(2);
		}
		else if(pid==-1){
			dprintf(1, "ERROR: during forking child\n");
			exit(1);
		}
		child[num_alive++]=pid;

		/*SET ALARM*/
		alarm(1);
	}

	/*KILLING AND CLOSING ALL PROCESS*/
	for(int i=0; i<num_alive; i++){
		kill(child[i], SIGINT);
	}
	while(wait(&status)!=-1){}

	/*FREE*/
	free(child);
	free(str_statuses);

	return 0;
}

void custom_handler(int signal){
	if(signal!=SIGALRM)
		return;

	/*DECIDE WHICH TO KILL*/
	int to_kill=rand()%num_alive;
	int pid_to_kill=child[to_kill];

	/*REORGANIZE DATA STRUCTURE*/
	child[to_kill]=child[--num_alive]; /*put last in place of killed*/

	/*KILL CHILD*/
	kill(pid_to_kill, SIGINT);

}