#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _strNode{
	char character;
	struct _strNode * next;
} strNode;

typedef struct _node{
	strNode * dynStr;
	struct _node * next;
} node;


/*FUNCTION*/
void list_free(node *);
void list_print(node *, FILE *);
void list_free_str(strNode *);
void list_print_str(strNode *, FILE *);


int main(int argc, char * argv[]){
	/*OPENING FILE*/
	FILE *input=fopen(argv[1], "r");
	FILE *output=fopen(argv[2], "w");

	if(input==NULL || output==NULL){
		printf("Error in opening files");
		return 1;
	}


	/*Initializing*/
	node *list=malloc(sizeof(*list)), *el;
	el=list;
	strNode * elStr=malloc(sizeof(*elStr));
	el->dynStr=elStr;
	elStr->character='\0';

	//Reading list
	int c=1;
	char res;
	res=fgetc(input);
	while(res!=EOF){
		if(res=='\n'){
			//new node
			el->next=malloc(sizeof(*(el->next)));
			el=el->next;
			c++;
			//new char
			elStr=malloc(sizeof(*elStr));
			el->dynStr=elStr;
			elStr->character='\0';
		}
		else{
			//save char
			elStr->character=res;
			//new char
			elStr->next=malloc(sizeof(*(elStr->next)));
			elStr=elStr->next;
			elStr->character='\0';
		}


		res=fgetc(input);
	}


	/*Make list circular*/
	el->next=list;

	/*print in random ->by freeing*/
	node *beforeEl=el;
	el=list;
	srand(time(0));
	for(;c>=1;c--){
		/*chose random element*/
		int random=(double)rand()/(RAND_MAX)*c;
		for(int i=0; i<random; i++){
			beforeEl=el;
			el=el->next;
		}
		/*print string*/
		list_print_str(el->dynStr, output);

		/*free element*/
		beforeEl->next=el->next;
		list_free_str(el->dynStr);
		free(el);
		el=beforeEl->next;
	}


	/*CLOSING -> to think*/
	fflush(NULL);
	fclose(input);
	fclose(output);


}

void list_free(node *el){
	/*FREEING RESURCES*/
	node *tempNext;
	strNode *elStr;
	while(el!=NULL){
		/*Free string*/
		list_free_str(el->dynStr);

		/*free node*/
		tempNext=el->next;
		free(el);
		el=tempNext;
	}
}

void list_free_str(strNode *elStr){
	strNode *tempNextStr;
	while(elStr!=NULL){
		tempNextStr=elStr->next;
		free(elStr);
		elStr=tempNextStr;
	}
}

void list_print(node *el, FILE *out){
	strNode *elStr;
	while(el!=NULL){
		list_print_str(el->dynStr, out);
		el=el->next;
	}
}

void list_print_str(strNode *elStr, FILE *out){
	while(elStr!=NULL && elStr->character!='\0'){
		putc(elStr->character, out);
		elStr=elStr->next;
	}
	putc('\n', out);
}
