#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PANIC_NUM(string, num) exit((dprintf(1, "FATAL (line: %d): %s [%d]\n", __LINE__, (string), (num)), 1))
#define PANIC(string) exit((dprintf(1, "FATAL (line: %d): %s\n", __LINE__, (string)), 1))

#define KEEP_IN_LIMITS(i, min, max)  (i)>(max) ? (min) : (i)
void handler(int);
int i;

int main(int argc, char **argv){
	/*DECLARATION*/
	struct sigaction sighandler;

	/*ARGUMENT CHECK AND OBTAIN VALUES*/
	if(argc<2)PANIC("not enougth parameters");
	i=argv[1][0];
	if(!(i>=33 && i<=126))PANIC_NUM("not valid parameter/s", i);

	/*CUSTOM HANDLER*/
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler;
	sigaction(SIGINT, &sighandler, NULL);

	/*INFINITE LOOP*/
	for(;; KEEP_IN_LIMITS(++i, 33, 126));
}

void handler(int signum){
	if(signum==SIGINT)
		exit(KEEP_IN_LIMITS(i, 33, 126));
}