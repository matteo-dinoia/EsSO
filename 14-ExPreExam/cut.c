struct node * cut(struct node * head, int begin, int end)
{
        node *tmp, *el, *next;
        if(head==NULL || begin>end) return NULL;

        el=head;
        for(int i=0; el!=NULL; i++){
                next=el->next;
                if(i<begin){
                        free(head);
                        head=next;
                }else if(i>end){
                        free(el);
                }else if(i==end){
                        el->next=NULL;
                }
                el=next;
        }

        return head;
}
