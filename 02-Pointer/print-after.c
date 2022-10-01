#include <stdio.h>

int main()
{
	int LEN=81;
	char s1[LEN], s2[LEN];

	//GET STRING
	printf("Insert first string:");
	fgets(s1, sizeof(s1), stdin);
	printf("Insert second string:");
	fgets(s2, sizeof(s2), stdin);

	//CLEAN FIRST STRING
	char *key=s1;
	while(*key!=0){
		if(*key<32 && *key>126){
			*key=0;
			break;
		}
		key=key+1;
	}

	//CLEAN FIRST STRING
	key=s2;
	while(*key!=0){
		if(*key<32 && *key>126){
			*key=0;
			break;
		}
		key=key+1;
	}

	//CHECKING
	char *str1=s1;
	while(*str1!=0){
		char *str2=s2, *temp1=str1;
		while(*str1!=0){
			if(*str2==0){
				printf("%s", temp1);
				return 0;
			}

			temp1=temp1+1;
			str2=str2+1;
		}
		str1=str1+1;
	}
}
