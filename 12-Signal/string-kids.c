#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define PANIC_NUM(string, num) exit((dprintf(1, "FATAL (line: %d): %s [%d]\n", __LINE__, (string), (num)), 1))
#define PANIC(string) exit((dprintf(1, "FATAL (line: %d): %s\n", __LINE__, (string)), 1))

int main(int argc, char **argv){
	/*DECLARATION*/
	int i, pid, status, num_child;
	int *child;
	char *const arg[]={"char-loop", "Hello", NULL};
	char *const env[]={NULL};

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<2)
		PANIC("not enougth parameters");
	num_child=atoi(argv[1]);
	if(num_child<=0)
		PANIC("negative or null parameter/s");

	/*CREATE CHILD*/
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


	/*KILL THEM*/
	sleep(1);
	for(i=0; i<num_child; i++)
		kill(child[i], SIGINT);


	/*GET SIGNAL*/
	while(wait(&status)!=-1)
		dprintf(1, "RETURN %d by child\n", WEXITSTATUS(status));


	return 0;
}
