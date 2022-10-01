#include <stdio.h>
#include <stdlib.h>
int main(){
	int LEN=7, m[LEN];
	char s[100];
	printf("Insert %d number:\n", LEN);
	for(int i=0; i<LEN; i++){
		fgets(s, sizeof(s), stdin);
		m[i]=strtol(s, NULL, 10);
	}
	int middle=LEN/2+LEN%2;
	for(int i=0; i<LEN; i++){
		if(i<middle) printf("%d", m[i*2]);
		else printf("%d", m[2*(i-middle)+1]);
	}
}
