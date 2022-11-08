#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler(int);

int i;

int main(int argc, char **argv){
	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<2){
		printf("ERROR: not enougth parameters\n");
		return 1;
	}
	i=argv[1][0];
	if(!(i>=33 && i<=126)){
		printf("ERROR: not valid parameter/s i=%d\n", i);
		return 1;
	}

	/*CUSTOM HANDLER*/
	struct sigaction sighandler;
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler;
	sigaction(SIGINT, &sighandler, NULL);

	/*INFINITE LOOP*/
	while(1){
		i++;
		if(i>126){i=33;}
	}


}

void handler(int signum){
	if(signum==SIGINT){
		exit(i);
	}
}