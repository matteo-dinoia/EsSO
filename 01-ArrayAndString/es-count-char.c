#include <stdio.h>
#include <string.h>

#define ENTER 10

int main(){
	char s[100];
	printf("Insert a string:");
	fgets(s, sizeof(s), stdin);
	int len=strlen(s);

	for(int i=0; i<len; i++){
		char key=s[i];
		int sum=0;
		int i2;
		for(i2=0; i2<len; i2++){
			if(key==s[i2]){
				if(i2<i)break;
				else sum++;
			}
		}
		if(i2==len){
			if(key==ENTER)
				printf("char  \\n  happened %d times\n", sum);
			else
				printf("char  %c   happened %d times\n", key, sum);
		}

	}
}
