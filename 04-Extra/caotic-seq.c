#include <stdio.h>

int caotic_seq_len(int num);

int main(){
	//GET MAX NUMBER
	int max=0;
	printf("Insert max number:");
	scanf("%d", &max);

	//PRINT
	for(int i=1; i<max; i++)
		printf("|caotic_seq(%d)|=%d\n", i, caotic_seq_len(i));
}

int caotic_seq_len(int num){
	//printf("%d ",num);

	if(num<1)
		return -1;
	else if(num<=1)
		return 1;
	else if(num%2==0)
		return 1+caotic_seq_len(num/2);
	else
		return 1+caotic_seq_len(num*3+1);
}
