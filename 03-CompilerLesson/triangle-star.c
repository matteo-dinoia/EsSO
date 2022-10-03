#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM 20

int main()
{
	//GET BASE AND HEIGHT
	int base, height;
	printf("Insert the base:");
	scanf("%d", &base);
	printf("Insert height:");
	scanf("%d", &height);

	//DRAW TRIANGLE
	int i, i2, hcount;
	for(i=0; i<height; i++){
		hcount=1+((double)(base-1)/(height-1))*i;
		for(i2=0; i2<hcount; i2++)
			printf("*");
		printf("\n");
	}
}
