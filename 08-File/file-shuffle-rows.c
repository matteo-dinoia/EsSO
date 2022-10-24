#include <stdio.h>
#include <stdlib.h>

int main(){
	/*OPENING FILE*/
	FILE *input=fopen("input.txt", "r");
	FILE *output=fopen("output.txt", "w");

	if(input==NULL || output==NULL){
		printf("Error in opening files");
		return;
	}


	while(){


	}

	/*CLOSING -> to think*/
	fflush(NULL);
	fclose(input);
	fclose(output);


}