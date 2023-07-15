#include<stdio.h>
#include<stdlib.h>
struct number
{
    int value;
    struct number *next;
};
struct operator
{
    char value;
    struct operator *next;
};

//based on the associativity and the precedence of the operators, made the inside and outside stack priorities for the operators
// +, * are the only left associative operators, the rest are right associative, they have the same precedence order

int inside_priority(char x)     //inside stack priority for operations
{
    if(x=='+')
    {
        return 1;
    }
    if(x=='-')
    {
        return 2;
    }
    if(x=='/')
    {
        return 4;
    }
    if(x=='*')
    {
        return 7;
    }
    if(x=='^')
    {
        return 8;
    }
    return 0;
}

int outside_priority(char x)     //outside stack priority for operations
{
    if(x=='+')
    {
        return 0;
    }
    if(x=='-')
    {
        return 3;
    }
    if(x=='/')
    {
        return 5;
    }
    if(x=='*')
    {
        return 6;
    }
    if(x=='^')
    {
        return 9;
    }
    return 0;
}

struct number *push_number(struct number *head, int x)     //pushing the number passed into the stack made for numbers
{
    struct number *temp=(struct number *)calloc(1, sizeof(struct number));
    temp->value=x;
    temp->next=head;
    return temp;
}

struct operator *push_operator(struct operator *head, char x)     //pushing the operator passed into the stack made for operators
{
    struct operator *temp=(struct operator *)calloc(1, sizeof(struct operator));
    temp->value=x;
    temp->next=head;
    return temp;
}

int power(int x, int y)
{
    int temp;
    if( y == 0)
    {
        return 1;
    }
    temp = power(x, y/2);
    if (y%2 == 0)
    {
        return temp*temp;
    }
    else
    {
        return x*temp*temp;
    }
}

int execute(int x, int y, char z)     //for executing the operator when the conditions are met
{
    if(z=='+')
    {
        return x+y;
    }
    if(z=='-')
    {
        return x-y;
    }
    if(z=='/')
    {
        return x/y;
    }
    if(z=='*')
    {
        return x*y;
    }
    if(z=='^')
    {
        return power(x,y);
    }
    return 0;
}

struct number *pop_number(struct number *number_head)     //popping the number when executing the operator
{
    struct number *temp=number_head;
    number_head=number_head->next;
    free(temp);
    return number_head;
}

struct operator *pop_operator(struct operator *operator_head)     //popping the operator when executing it
{
    struct operator *temp=operator_head;
    operator_head=operator_head->next;
    free(temp);
    return operator_head;
}

int count_them(int x)     //for counting the number of digits in the integer scanned which in turn gives us number of charecters scanned in this scanf
{
    int n=0;
    if(x==0)
    {
        return 1;
    }
    while(x>0)
    {
        x/=10;
        n++;
    }
    return n;
}

int main()
{
    int n, x, number_of_scans=0;     //number_of_scans storest the number of characters already scanned
    char y;
    struct number *number_head=NULL;
    struct operator *operator_head=NULL;
    scanf("%d", &n);     //stores the total number of charecters in the string (numbers+operations)
    while(1)
    {
        scanf("%d", &x);     //x stores the current number
        number_of_scans+=count_them(x);
        if(number_of_scans==n)
        {
            break;
        }
        scanf("%c", &y);     //y stores the current operator
        number_of_scans++;
        while(operator_head!=NULL && inside_priority(operator_head->value)>outside_priority(y))     //condition for execution
        {
            x=execute(number_head->value, x, operator_head->value);
            number_head=pop_number(number_head);
            operator_head=pop_operator(operator_head);
        }
        number_head=push_number(number_head, x);
        operator_head=push_operator(operator_head, y);
    }
    while(operator_head!=NULL)     //the operator stack will have all the operators arranged so one can execute without checking any condition
    {
        x=execute(number_head->value, x, operator_head->value);
        number_head=pop_number(number_head);
        operator_head=pop_operator(operator_head);
    }
    printf("%d", x);     //x will be storing the answer for the expression, number and operator heads will be null
    return 0;
}