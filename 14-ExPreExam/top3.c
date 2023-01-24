typedef struct node {
    int val;
    struct node * next;
} nodo;

nodo *insert_sorted_decresc(nodo *head, nodo *to_insert){
    if(head==NULL) return to_insert;
    else if(to_insert==NULL) return head;
    else if(to_insert->val >= head->val){
        to_insert->next=head;
        return to_insert;
    }

    nodo *tmp
    for(nodo *el=head; el!=NULL;){
        if(el->next==NULL || el->next->val <= to_insert->val){
            tmp=el->next;
            el->next=to_insert;
            to_insert->next=tmp;
            break;
        }
    }

    return head;
}

nodo * top3(nodo *head){
    if(head==NULL) return NULL;

    node *res=NULL, next;
    for(;head!=NULL; head=next){
        next=head->next;
        res=insert_sorted_decres(res, head);
    }


    node *tmp
    for(int i=0, node *el=res; el!=NULL ;i++)
        if(i>=3){
            tmp=el;
            el=el->next;
            free(tmp);
        }
        else el=el->next;
    }


    return res;
}
