#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node * next;   /* pointer to the same structure */
} node;
typedef node* list;

//DEFINITION
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

//EXTRA ES
/*
 * la quale cancella e dealloca il primo nodo della lista il cui valore del campo value `e uguale al parametro to delete. La
 * funzione restituisce la lista cos`ı modificata.
 */
list list_delete_if(list, int);
/*
 * la quale rimuova dalla lista ogni elemento in posizione dispari (il primo, il terzo, etc.).
 * La funzione restituisce la lista cos`ı modificata.
 */
list list_delete_odd(list);
/*
 * la quale rimuova dalla lista ogni elemento che abbia valore inferiore al valore cut_value passato come parametro.
 */
list list_cut_below(list, int);
/*
 * la quale ritorna una copia dalla lista (copia di ogni elemento).
 */
list list_dup(list);


//FUNCTION
int main()
{
	list head = NULL, head2=NULL;

	/* insert some numbers in the list... */
	head = list_insert_ordered(head, 10);
	head = list_insert_ordered(head, 2);
	head = list_insert_ordered(head, 15);
	head = list_insert_ordered(head, 10);
	head = list_insert_ordered(head, 10);
	head = list_insert_ordered(head, 21);
	head = list_insert_ordered(head, 1);
	head = list_insert_ordered(head, -2);
	head = list_insert_ordered(head, 12);
	head = list_insert_ordered(head, 14);
	head = list_insert_ordered(head, 5);
	head = list_insert_ordered(head, 6);

	head2 = list_insert_ordered(head2, 7);
	head2 = list_insert_ordered(head2, 4);
	head2 = list_insert_ordered(head2, 3);
	head2 = list_insert_head(head2, 700);
	head2 = list_insert_tail(head2, 1);
	head2 = list_insert_tail(head2, 7);


	/* ... print them... */
	list_print(head);
	list_print(head2);

	head=list_delete_odd(head);
	head2=list_cut_below(head2, 7);
	list head3 = list_dup(head2);

	/* ... print them... */
	list_print(head);
	list_print(head2);
	list_print(head3);

	head2=list_cut_below(head2, 8);

	/* ... print them... */
	list_print(head);
	list_print(head2);
	list_print(head3);

	/* ... and clean everything up  */
	list_free(head);
	list_free(head2);
	list_free(head3);

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
	p->next=list_insert_ordered(p->next, val);
	return p;
}

//EXTRA FUNCTION
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
	/*if(head==NULL)
		return NULL;
	else if(head->value==to_delete){
		list el = head->next;
		free(head);
		return el;
	}

	list tmp=head;
	while (tmp->next != NULL){
		if(tmp->next->value==to_delete){
			list el = tmp->next;
			tmp->next = tmp->next->next;
			free(el);
			return head;
		}
		tmp = tmp->next;
	}

	return head;*/
}

list list_delete_odd(list head)
{
	if(head==NULL)
		return NULL;

	list newHead = head->next, tmp=newHead, newNext;
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


		/*
	if(head==NULL)
		return NULL;

	list newHead = NULL, tmp=head, newNext;

	if(head->value >=cut_value)
		newHead = head;

	while(tmp!=NULL && tmp->next!=NULL){
		if(tmp->next->value < cut_value){
			list el = tmp->next;
			tmp->next = tmp->next->next;

			free(el);
		}
		else{
			if(newHead==NULL)
				newHead = tmp;
			else{

			}
		}
		tmp = tmp->next;
	}

	return newHead;*/
}

list list_dup(list head)
{
	if(head==NULL)
		return NULL;


	list newNode;
	newNode=malloc(sizeof(*newNode));
	newNode->value = head->value;
	newNode->next=list_dup(head->next);
	return newNode;
}