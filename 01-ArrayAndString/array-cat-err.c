/* Codice che concatena le due stringhe v1 e v2 */
#include <stdio.h>
#include <string.h>
int main()
{
	char v1[100] = "Prima,";
	char v2[100] = " dopo";
	int len1, len2, i;


	 /* Lunghezza delle due stringhe */
	len1 = strlen(v1);
	len2 = strlen(v2);

	//check
	if(len1+len2+1>=100) return -1;

	/* Stampa delle due stringhe */
	printf("String 1: '%s'\n", v1, len1);
	printf("String 2: '%s'\n", v2, len2);

	/* Copia la seconda stringa alla fine della prima */
	for (i=0; i<len2+1; i++)
		v1[len1+i] = v2[i];

	/* Stampa la stringa concatenata */
	printf("String concatenated: '%s'\n", v1);

}
