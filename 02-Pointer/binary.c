#include <stdio.h>
#include <stdlib.h>

int main()
{
	char s[10], res[100], *str=&res[99];

	//READ NUMBER
	printf("Insert a number:");
	fgets(s, sizeof(s), stdin);
	int number=strtol(s, NULL, 10);

	//EXCLUDE NEGATIVE NUMBER
	if(number<0){
		printf("Only accectable value are positive value");
		return 1;
	}

	//CONVERT
	int mask=1;
	*str=0;
	do{
		str=str-1;
		*str=48+(mask&number);
		number=number>>1;
	}while(number>0);

	printf("%s", str);
}
