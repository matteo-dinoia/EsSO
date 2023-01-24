#include <stdlib.h>
#include <stdio.h>
typedef struct _node {
    int val;
    struct _node *next;
} node;

typedef node *list;

int conta_valori(list ls, int val){
   if (ls!=NULL)
      return ls->next!=NULL ? conta_valori(ls->next->next, val) + (ls->val==val) : ls->val==val ;
   return 0;
}

int conta_valori2(list ls, int val){
 if(ls==NULL) return 0;

 int c= (ls->val==val)?1:0;
 if(ls->next==NULL) return c;
 else return c + conta_valori2(ls->next->next, val);
}

void plist(list ls){
    if(ls==NULL) return;
    printf("%d ", ls->val);
    plist(ls->next);
}
int main(){
    list head = malloc(sizeof(list)), el;
    head->val=1;
    el=head;

    el = el->next = malloc(sizeof(list));
    el->val=2;

    el = el->next = malloc(sizeof(list));
    el->val=2;

    el = el->next = malloc(sizeof(list));
    el->val=0;

    el = el->next = malloc(sizeof(list));
    el->val=2;

    el = el->next = malloc(sizeof(list));
    el->val=0;

    el = el->next = malloc(sizeof(list));
    el->val=3;

    el = el->next = malloc(sizeof(list));
    el->val=2;

    el = el->next = malloc(sizeof(list));
    el->val=2;

    printf("%d %d\n", conta_valori(head, 2), conta_valori2(head, 2));
    plist(head);
    return 0;
}
