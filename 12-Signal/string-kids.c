#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

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

	/*CREATE CHILD*/
	int pid;
	int *child=calloc(num_child, sizeof(*child));
	for(int i=0; i<num_child; i++){
		if((pid=fork())==0){/*CHILD*/
			free(child);
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

	sleep(1);
	/*KILL THEM*/
	for(int i=0; i<num_child; i++){
		kill(child[i], SIGINT);
	}

	/*GET SIGNAL*/
	int status;
	while(wait(&status)!=-1){
		dprintf(1, "RETURN %d by child\n", WEXITSTATUS(status));
	}

	return 0;
}
