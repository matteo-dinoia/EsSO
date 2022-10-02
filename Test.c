#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM 20

int main()
{

	printf("Creating %d process\n", NUM); //Ask proff

	//CREATING PROCESS
	int pidFather=getpid();
	for(int i=0; i<NUM; i++){
		int pid=fork();
		if(pid<0){
			printf("Error while forking\n");
		}
		else if(pid==0){
			break;
		}
	}

	//CLOSING
	if(pidFather==getpid())
		printf("(Father: %d) Shutting down\n", getpid());
	else
		printf("(Son: %d)    Shutting down\n", getpid());
	exit(0);
}
