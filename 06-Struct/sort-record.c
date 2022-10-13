#include <stdio.h>
#include <stdlib.h>


#define NUM 10
#define MAX_LEN  10
#define MIN_AGE 18
#define MAX_AGE 120

typedef struct {
	char * name ;
	int age ;
} record ;

//FUNCTION PROTOTYPE
record * rec_rand_create ( int n ) ;
void rec_sort ( record * v , int n ) ;
void rec_print ( record * v , int n ) ;
void rec_free ( record * v , int n ) ;
int randIn(int min, int max);

int main(void)
{
	record *list;

	list = rec_rand_create(NUM);
	rec_print(list, NUM);

	//TEST
	printf("\nSORT\n");
	rec_sort(list, NUM);
	rec_print(list, NUM);
}

record * rec_rand_create ( int n ){
	//ALLOCCATE
	record *head, *actual;
	head = calloc(NUM, sizeof(*head));


	//CREATE DATA
	for (int i = 0; i < n; i++){
		actual = head+i;
		actual->age = randIn(MIN_AGE, MAX_AGE);

		//create string
		int length = randIn(1, MAX_LEN), j;
		actual->name = calloc(length+1, sizeof(*(actual->name)));
		for (j = 0; j < length; j++){
			(actual->name)[j] = randIn(65, 90);
		}
		(actual->name)[j] = 0;

		actual += 1;
	}

	return head;
}

void rec_print ( record * v , int n ){
	//EXIT CASE
	if(n<=0)
		return;

	//PRINT AND RECURSIVE
	printf("%s (%d)\n", v->name, v->age);
	rec_print(v + 1, n-1);
}

void rec_free ( record * v , int n ){ //tectnically can be done recursive
	for (int i = 0; i < n; i++)
		free((v + i)->name);
	free(v);
}

void rec_sort ( record * v , int n ){
	for (int i = 0; i < n-1; ){
		if(((v+i)->age) > ((v+i+1)->age)){
			record t = *(v + i);
			*(v + i) = *(v + i + 1);
			*(v + i + 1) = t;

			if(i>0)
				i--;
		}
		else
			i++;
	}
}

int randIn(int min, int max){
	return min + rand()%(max - min+1);
}