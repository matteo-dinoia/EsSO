
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]){

	/*CONTROL FOR ZERO ARGUMENT*/
	if(argc<=1){
		printf("ERROR: add an argument!");
		return -1;
	}

	/**OPEN FILE*/
	int input=open(argv[1], O_RDONLY);

	/*CHECK IF ERROR*/
	if(errno==ENOENT){
		int output=open("file.txt", O_WRONLY|O_CREAT, 0777);
		dprintf(output, "Ciao a tutti");
		close(output);

		input=open("file.txt", O_RDONLY);
	}

	/*READ FILE*/
	unsigned char buf[100];
	int nRead;
	int res=0;
	do{
		nRead=read(input, buf, sizeof(buf));
		for(int i=0; i<nRead; i++){
			res=(res+buf[i])%256;
			putc(buf[i], stdout);
		}
	}while(nRead!=0 && nRead!=-1);

	/*PRINT RES AND CLOSE*/
	printf("Sum of all byte is: %d", res);
	close(input);
	return 0;
}