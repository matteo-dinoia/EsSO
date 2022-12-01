#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	//GET THE DOUBLE
	char s[100];
	printf("Write a double: ");
	fgets(s, sizeof(s), stdin);
	double number=atof(s);

	//CALCULATE
	unsigned long *value, mask, res;
	mask=2047;
	mask=mask<<52;
	value=(unsigned long*)&number;

	//RESULT
	res=(*value & mask);
	res=res>>52;
	printf("Hexadecimal Value (not removed 1023): %03X\nExponent: %d\n", res, res-(1024-1));
}