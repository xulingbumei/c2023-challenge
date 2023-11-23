#include <stdio.h>
#include<malloc.h>
#include<time.h>
typedef struct LIST{
    int number;
    int data;
    struct LIST* next;
}linked_list;

linked_list *create_linked_list(int n);
void print(linked_list * P);
linked_list *reverse(linked_list*head);
int search_forfirstfive(linked_list * P,int ii);
int search_forseconmdfive(linked_list * P,int ii){
    int num=0,flag=0;
    while(P!=NULL){
        if(P->data==ii&&flag==0){
            flag=1;
        }else if(P->data==ii&&flag==1){
            return num;
        }
        P=P->next;
        num++;
    }

    if(P->data!=ii){
        return -1;
    }

}
int main()
{
    int n,number1,number2;
    linked_list *head=NULL,*p1=NULL;
    printf("put a number that bigger than five\n");
    scanf("%d",&n);
    head=create_linked_list(n);
    printf("the linked_list is\n");
    print(head);
    p1=reverse(head);
    printf("the reversed link_list is\n");
    print(p1);
    number1= search_forfirstfive(p1,5);
    printf("the first five locate in %d\n",number1);
    number2= search_forseconmdfive(p1,5);
    printf("the second five locate in %d\n",number2);
    return 0;
}

linked_list *create_linked_list(int n)
{
    linked_list *head=NULL;
    srand( (unsigned)time( NULL ) );
    for(int i=n;i>0;i--){
        int k=0;
        k=rand()/3276.7;//随机生成数字
        linked_list *new=(linked_list*)malloc(sizeof(linked_list));
        new->data= k;
        new->next=head;
        new->number=i;
        head=new;
    }
    return head;
};
void print(linked_list * P)
{
    while(P!=NULL)
    {
        printf("%d:%d ",P->number,P->data);
        P=P->next;
    }
    printf("\n");
    return;
}
linked_list *reverse(linked_list*head){
    linked_list*prehead=NULL,*temp=NULL;
    while(head!=NULL){
        temp=head;
        head=head->next;
        temp->next=prehead;
        prehead=temp;
    }
    return prehead;
}
int search_forfirstfive(linked_list * P,int ii){
    int num=0;
    while(P!=NULL){
        if(P->data==ii){
            return num;
            break;
        }
        P=P->next;
        num++;
    }
    if(P->data!=ii){
        return -1;
    }

}