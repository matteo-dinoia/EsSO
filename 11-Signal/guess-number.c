#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PANIC_NUM(string, num) exit((dprintf(1, "FATAL (line: %d): %s [%d]\n", __LINE__, (string), (num)), 1))
#define PANIC(string) exit((dprintf(1, "FATAL (line: %d): %s\n", __LINE__, (string)), 1))

void handler(int);

int main(int argc, char **argv){
	/*DECLARATION*/
	struct sigaction sighandler;
	int max_number, guess_number, guess_time, v;

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<3)
		PANIC("not enougth parameters");
	srand(time(NULL));
	max_number=atoi(argv[1]);
	guess_time=atoi(argv[2]);
	if(guess_time<=0 || max_number<=0)
		PANIC("negative or null parameter/s");

	/*SELECT A NUMBER RANDOM*/
	guess_number = rand() % (max_number + 1);

	/*SETUP HANDLER*/
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler;
	sigaction(SIGALRM, &sighandler, NULL);

	/*START TIMER*/
	alarm(guess_time);

	/*GAME*/
	printf("Insert a guess: ");
	v=-1;
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
	const char str[] = "\n\nYou lose\n\n";

	if(signum!=SIGALRM)
		return;

	write(1, str, sizeof(str));
	exit(0);
}