#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void handler(int);

int main(int argc, char **argv){
	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3){
		printf("ERROR: not enougth parameters");
		return 1;
	}
	srand(time(0));
	int max_number=atoi(argv[1]);
	int time=atoi(argv[2]);
	if(time<=0 || max_number<=0){
		printf("ERROR: negative or null parameter/s");
		return 1;
	}

	/*SELECT A NUMBER RANDOM*/
	int guess_number = rand() % (max_number + 1);

	/*SETUP HANDLER*/
	struct sigaction sighandler;
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler;
	sigaction(SIGALRM, &sighandler, NULL);

	/*START TIMER*/
	alarm(time);

	/*GAME*/
	printf("Insert a guess: ");
	int v=-1;
	while (v!=guess_number){
		scanf("%d", &v);
		if(v>guess_number)
			printf("Too big of number. Retry:");
		else if (v < guess_number)
			printf("Too small of number. Retry:");
	}

	/*WINNIG*/
	printf("\nYou won\n\n");
	return 0;
}

void handler(int signum){
	if(signum==SIGALRM){
		char c[] = "\n\nYou lose\n\n";
		write(1, c, sizeof(c));
		exit(0);
	}

}