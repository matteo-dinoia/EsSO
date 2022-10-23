#include <stdio.h>
#include <stdlib.h>

unsigned long my_str_to_long(char * str);

int main(int argc, char * argv[]){
	for (int i = 1; i < argc; i++){
		printf("'%s'= _%lu_\n", argv[i], my_str_to_long(argv[i]));
	}
}

unsigned long my_str_to_long(char * str){
	if(str==(char *) 0)
	return 0;

	unsigned long res=0;

	while (*str>='0' && *str <='9'){
		res=res*10+(*str-'0');
		str=str+1;
	}

	return res;
}

//NO TEST DONE
typedef struct _node{
	int val;
	struct _node *next;
} node;

node * list_trim(node *head)
{
	if(head==(node *) 0)
		return head;

	int lastVal=head->val;
	node * actual=head->next, *old=head;
	while(actual!=(node *) 0){
		if(actual->val==lastVal){
			old->next=actual->next;
			free(actual);
			actual=old->next;
		}
		else{
			old=actual;
			lastVal = actual->val;
			actual = actual->next;
		}
	}

	return head;
}

node * list_trim_R(node *head)
{
	if(head==(node *) 0 || head->next==(node *) 0)
		return head;

	if(head->val == head->next->val){
		node *tempNext = head->next;

		head->next = tempNext->next;
		free(tempNext);

		list_trim_R(head);
	}
	else{
		list_trim_R(head->next);
	}



	return head;
}
