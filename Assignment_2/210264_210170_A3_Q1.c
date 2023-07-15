#include<stdio.h>
#include<stdlib.h>
int count=0;     //keeping the count of number of nodes in the stack made
struct point
{
    int value;
    struct point *next;
};

struct point *push(struct point *head)     //pushing into stack
{
    int x;
    scanf("%d", &x);
    struct point *temp=(struct point *)calloc(1, sizeof(struct point));
    temp->value=x;
    temp->next=head;
    return temp;
}

struct point *pop(struct point *head)     //popping the element from the stack
{
    if(head!=NULL)
    {
        printf("%d\n", head->value);
        struct point *temp=head;
        head=head->next;
        free(temp);
        count--;
    }
    else
    {
        printf("!\n");
    }
    return head;
}

void top(struct point *head)     //function for printing the value of the top of the stack 
{
    if(head!=NULL)
    {
        printf("%d\n", head->value);
    }
    else
    {
        printf("!\n");
    }
}

int main()
{
    int n, a;
    struct point *head=NULL;
    scanf("%d", &n);        //number of inputs
    while(n>0)
    {
        scanf("%d", &a);
        if(a==0)     //pushing
        {
            head=push(head);
            count++;
        }
        if(a==1)     //popping
        {
            head=pop(head);
        }
        if(a==2)     //top
        {
            top(head);
        }
        if(a==3)     //number of nodes in the stack
        {
            printf("%d\n", count);
        }
        n--;
    }
    return 0;
}