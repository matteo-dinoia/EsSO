#ifndef _LIST_MODULES_H
#define _LIST_MODULES_H

typedef struct _node* list;

list list_insert_ordered(list p, int val);
list list_cat(list before, list after);
list list_insert_head(list p, int val);
list list_insert_tail(list p, int val);
void list_print(list p);
void list_free(list p);

list list_delete_if(list, int);
list list_delete_odd(list);
list list_cut_below(list, int);
list list_dup(list);
#endif