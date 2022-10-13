#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* pointer to the same structure */
} node;
typedef node* list;

/*
 * Assume that the list is in increasing order and insert the element
 * preserving the increasing order
 */
list list_insert_ordered(list p, int val);
/*
 * Concatenate two lists
 */
list list_cat(list before, list after);
/*
 * Insert elements at the head of the list
 */
list list_insert_head(list p, int val);
/*
 * Insert elements at the tail of the list
 */
list list_insert_tail(list p, int val);
/*
 * Print the list content
 */
void list_print(list p);
/*
 * Free the list
 */
void list_free(list p);

int main()
{
	list head = NULL, head2=NULL;

	/* insert some numbers in the list... */
	head = list_insert_ordered(head, 10);
	head = list_insert_ordered(head, 2);
	head = list_insert_ordered(head, 15);

	head2 = list_insert_ordered(head2, 7);
	head2 = list_insert_ordered(head2, 4);
	head2 = list_insert_ordered(head2, 3);
	head2 = list_insert_head(head2, 700);
	head2 = list_insert_tail(head2, 1);


	/* ... print them... */
	list_print(head);
	list_print(head2);

	head=list_cat(head, head2);
	list_print(head);

	/* ... and clean everything up  */
	list_free(head);
	//list_free(head2);

	return 0;
}

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