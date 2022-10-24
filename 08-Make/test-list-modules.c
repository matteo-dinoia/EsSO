#include <stdio.h>
#include <stdlib.h>
#include "list-modules.h"

int main()
{
	list head = NULL, head2=NULL;

	/* insert some numbers in the list... */
	head = list_insert_ordered(head, 10);
	head = list_insert_ordered(head, 2);
	head = list_insert_ordered(head, 15);
	head = list_insert_ordered(head, 10);

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