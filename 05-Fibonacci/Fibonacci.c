#include <stdio.h>
#include <stdlib.h>

int * fibo(int);

int main(void){
	//GET NUMBER OF ELEMENT TO GET
	printf("Insert number of element of Fibonacci to print: ");
	int n, *res;
	scanf("%d", &n);

	//GET FIBONACCI SERIES
	res=fibo(n);

	//IF ERROR VALUE STOP
	if(res!=NULL) return;

	//PRINT FIBONACCI
	for(int i=0; i<n; i++)
		printf("%d ", res[i]);

	//DEALLOCCATION
	free(res);
}

int * fibo(int n){
	//CHECK FOR NEGATIVE NUMBER
	if(n<=0) return NULL;

	//ALLOCATION OF MEMORY
	int *p, actual=1, prec=0;
	p=calloc(n, sizeof(*p));

	//CREATION OF ELEMENT
	for(int i=0; i<n; i++){
		p[i]=actual;
		int t=actual;
		actual+=prec;
		prec=t;
	}
	return p;
}
