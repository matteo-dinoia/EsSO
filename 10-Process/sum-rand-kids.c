#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#ifndef NUM_KIDS
#define NUM_KIDS 20
#endif

int main(){
	/*CREATE CHILD*/
	int i, pid, ret_val;
	for (i = 0; i < NUM_KIDS; i++){
		pid=fork();
		if(pid==0){ /*CHILD*/
			srand(getpid());
			ret_val = rand() % 6 + 1;
			printf("PID child %d created value: %d\n", getpid(), ret_val);
			exit(ret_val);
		}
		else if (pid == -1){ /*ERROR*/
			fprintf(stderr, "Error creating child\n");
			return 0;
		}
	}

	/*FATHER*/
	int sum = 0, status = 0;
	while (wait(&status)!=-1)
		sum += WEXITSTATUS(status);

	/*PRINT RES*/
	printf("Sum is: %d\n", sum);
	return 0;
}
