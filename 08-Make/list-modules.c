#include "list-modules.h"
#include <stdlib.h>
#include <stdio.h>

struct _node {
	int value;
	struct _node * next;   /* pointer to the same structure */
};


void list_print(list p)
{
	if(p==NULL){
		printf("\n\n");
		return;
	}

	printf("%d ", p->value);
	list_print(p->next);
}

void list_free(list p)
{
	if(p==NULL){
		return;
	}

	/*Order is important*/
	list_free(p->next);
	free(p);
}

list list_insert_head(list p, int val)
{
	/*ALLOCCATE*/
	list res;
	res = malloc(sizeof(*res));

	/*PUT VALUE*/
	res->next = p;
	res->value = val;
	return res;
}

list list_insert_tail(list p, int val)
{
	if(p->next==NULL){
		list last;
		last = malloc(sizeof(*last));

		last->value = val;
		p->next = last;
	}
	else
		list_insert_tail(p->next, val);
	return p;
}

list list_cat(list before, list after)
{
	if(before->next==NULL)
		before->next = after;
	else
		list_cat(before->next, after);

	return before;
}

list list_insert_ordered(list p, int val){
	if(p==NULL || val < p->value){ /*FIRST ELEMENT*/
		list first;
		first = malloc(sizeof(*first));

		first->value = val;
		first->next = p;
		return first;
	}
	else if(p->next==NULL || val < p->next->value){ /*IN MIDDLE*/
		list middle;
		middle = malloc(sizeof(*middle));
		middle->value = val;

		middle->next = p->next;
		p->next = middle;
	}
	else /*NOT FOUND PLACE*/
		list_insert_ordered(p->next, val);
	return p;
}

/*EXTRA FUNCTION*/
list list_delete_if(list head, int to_delete)
{
	if(head==NULL)
		return NULL;
	else if(head->value != to_delete){
		list newNode;
		newNode=malloc(sizeof(*newNode));
		newNode->value = head->value;
		newNode->next=list_delete_if(head->next, to_delete);
		return newNode;
	}
	else{
		list next=head->next;
		free(head);
		return next;
	}
}

list list_delete_odd(list head)
{
	list newHead = head->next, tmp=newHead, newNext;

	if(head==NULL)
		return NULL;


	free(head);

	while(tmp!=NULL && tmp->next!=NULL){
		newNext = tmp->next->next;
		free(tmp->next);
		tmp->next = newNext;

		tmp = tmp->next;
	}

	return newHead;
}

list list_cut_below(list head, int cut_value)
{
	if(head==NULL){
		return NULL;
	}
	else if(head->value >=cut_value){
		list newNode;
		newNode=malloc(sizeof(*newNode));
		newNode->value = head->value;
		newNode->next=list_cut_below(head->next, cut_value);
		return newNode;
	}
	else{
		list next=head->next;
		free(head);
		return list_cut_below(next, cut_value);
	}
}

list list_dup(list head)
{
	list newNode;

	if(head==NULL)
		return NULL;



	newNode=malloc(sizeof(*newNode));
	newNode->value = head->value;
	newNode->next=list_dup(head->next);
	return newNode;
}