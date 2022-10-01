#include <stdio.h>
#include <stdlib.h>
int main(){
	int LEN=10, m[LEN], sum[LEN];
	char s[100];

	for(int i=0; i<LEN; i++){
		printf("Insert %d/%d number:", (i+1), LEN);
		fgets(s, sizeof(s), stdin);
		m[i]=strtol(s, NULL, 10);
	}

	//CALCULATE
	sum[LEN-1]=m[LEN-1];
	for(int i=LEN-2; i>=0; i--)
		sum[i]=m[i]+sum[i+1];


	//PRINT
	printf("\nResult: ");
	for(int i=0; i<LEN; i++)
		printf("%d ", sum[i]);
	printf("\n");
}
