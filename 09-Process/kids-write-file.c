
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	/*GET ATTRIBUTE*/
	if(argc<4){
		printf("ERROR: too few arguments");
		return -1;
	}
	int n_kids=atoi(argv[2]), n_writes=atoi(argv[3]);

	/*OPENING FILE*/
	FILE * output=fopen(argv[1], "w");
	if(output==NULL){
		printf("ERROR: during opening file");
		return -1;
	}
	//setvbuf(output, NULL, _IONBF, 0);

	/*CREATE PROCESS*/
	int pid=1;
	for(int i=0; i<n_kids && pid>0; i++){
		pid=fork();
	}

	/*FATHER HAS FINISHED ->END OR ERROR*/
	if(pid==-1){
		printf("ERROR: during forking");
		return -1;
	}
	if(pid!=0){
		return 0;
	}


	/*WRITING*/
	for(int i=0; i<n_writes; i++){
		fprintf(output, "Figlio: %d, Padre. %d\n", getpid(), getppid());
	}
	fflush(NULL);
	fclose(output);

}