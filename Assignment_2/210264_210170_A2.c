#include<stdio.h>
#include<stdlib.h>
int i=0;            //flag for null matrix
struct point
{
    int i;
    int j;
    int value;
    struct point *next;
    struct point *down;
};

struct point *list_add_row(struct point *row, int i)            //function to add a new row to matrix 1 at the end (adding a node to list)
{
    struct point *temp=(struct point *)calloc(1, sizeof(struct point));
    temp->i=i;
    if(row!=NULL)
    {
        row->down=temp;
    }
    else
    {
        row=temp;
    }
    return temp;
}

struct point *list_add_column(struct point *column, int j, int flag)            //fuction to add a new column in matrix 2 (adding a node to list)
{
    if(flag==0)
    {
        struct point *temp1=column->next;
        struct point *temp=(struct point *)calloc(1, sizeof(struct point));
        temp->j=j;
        column->next=temp;
        temp->next=temp1;
        return temp;
    }
    else
    {
        struct point *temp=(struct point *)calloc(1, sizeof(struct point));
        temp->j=j;
        if(column!=NULL)
        {
            column->next=temp;
        }
        else
        {
            column=temp;
        }
        return temp;
    }
}

struct point *get_row(struct point *cell_needed, int i)          // returns the needed cell
{
    if(cell_needed!=NULL)
    {
        while(cell_needed->down!=NULL)           //while loop for going to lowest row
        {
            cell_needed=cell_needed->down;
        }
        if(i==cell_needed->i)           //if the i value of lowest row is same as the i provided return the last element in this row
        {
            while(cell_needed->next!=NULL)
            {
                cell_needed=cell_needed->next;
            }
        }
        else            //if the i value is less than the one provided add the next row and return it
        {
            cell_needed=list_add_row(cell_needed, i);
        }
    }
    else
    {
        cell_needed=list_add_row(cell_needed, i);
    }
    return cell_needed;
}

struct point *get_column(struct point *cell_needed, int j)          // returns the needed cell
{
    if(cell_needed!=NULL)
    {
        while(cell_needed->next!=NULL)           //while loop for searching the column header with j value greater than the j provided
        {
            if((cell_needed->next->j)>j)
            {
                break;
            }
            cell_needed=cell_needed->next;
        }
        if(j==cell_needed->j)           //if the cell is found to have the same j value then go down the column to the end so as to add the new element below
        {
            while(cell_needed->down!=NULL)
            {
                cell_needed=cell_needed->down;
            }
        }
        else if((cell_needed->j)<j)         //if column header with same j value does not exist, make it
        {
            cell_needed=list_add_column(cell_needed, j, 0);
        }
    }
    else            //j given is greater than all the j values of column headers
    {
        cell_needed=list_add_column(cell_needed, j, 1);
    }
    return cell_needed;
}

struct point *get_matrix1(struct point *matrix)
{
    struct point *cell = matrix;            //cell for traversing the matrix 1 to point at proper element
    struct point *temp=(struct point *)calloc(1, sizeof(struct point));
    scanf("%d %d %d", &(temp->i), &(temp->j), &(temp->value));
    cell=get_row(cell, temp->i);            //get_row makes the cell point to the element needed
    if(matrix==NULL)
    {
        matrix=cell;
    }
    cell->next=temp;            //addin the cell to the data structure
    return matrix;
}

struct point *get_matrix2(struct point *matrix)
{
    struct point *cell = matrix;            //cell for traversing the matrix 1 to point at proper element
    struct point *temp=(struct point *)calloc(1, sizeof(struct point));
    scanf("%d %d %d", &(temp->i), &(temp->j), &(temp->value));
    cell=get_column(cell, temp->j);            //get_column makes the cell point to the element needed
    if(matrix==NULL)
    {
        matrix=cell;
    }
    cell->down=temp;            //addin the cell to the data structure
    return matrix;
}

void multiply(struct point *row1, struct point *column2)              //function for multiplying the given row and column and outputting the value
{
    struct point *clm2 = column2;
    struct point *rw1 = row1;
    int temp=0;
    while(rw1!=NULL && clm2!=NULL)
    {
        if(rw1->j==clm2->i)
        {
            (temp)+=((rw1->value)*(clm2->value));
            rw1=rw1->next;
            clm2=clm2->down;
        }
        else if((rw1->j)<(clm2->i))
        {
            rw1=rw1->next;
        }
        else
        {
            clm2=clm2->down;
        }
    }
    if(temp!=0)
    {
        printf("%d %d %d\n", row1->i, column2->j, temp);
        i++;
    }
}

void free_matrix1(struct point *matrix)
{
    while(matrix!=NULL)
    {
        struct point *temp=matrix;
        matrix=matrix->down;
        while(temp!=NULL)
        {
            struct point *temp1=temp;
            temp=temp->next;
            free(temp1);
        }
    }
}

void free_matrix2(struct point *matrix)
{
    while(matrix!=NULL)
    {
        struct point *temp=matrix;
        matrix=matrix->next;
        while(temp!=NULL)
        {
            struct point *temp1=temp;
            temp=temp->down;
            free(temp1);
        }
    }
}

int main()
{
    int n, a;
    struct point *matrix1=NULL;
    scanf("%d", &n);            //n will store the size of the matrix
    while(1)
    {
        scanf("%d", &a);            //a will tell the matrix for which the value is input
        if(a!=1)
        {
            break;
        }
        matrix1=get_matrix1(matrix1);           //get_matrix1 takes the input and stores them in the data structure made for matrix 1
    }
    struct point *matrix2=NULL;
    while(a!=0)
    {
        matrix2=get_matrix2(matrix2);           //get_matrix1 takes the input and stores them in the data structure made for matrix 2
        scanf("%d", &a);
    }
    struct point *cell1=NULL;
    struct point *cell2=NULL;       //cell1 & cell2 will help in multiplication of matrix by traversing the row heads and column heads respectively
    cell1=matrix1;
    while(cell1!=NULL)          //for traversing rows of matrix 1
    {
        cell2=matrix2;
        while(cell2!=NULL)          //for traversing columns of matrix 2
        {
            multiply(cell1->next, cell2->down);         //function for multiplying the given row and column and outputting the value
            cell2=cell2->next;          //pointing to next column
        }
        cell1=cell1->down;          //next row
    }
    free_matrix1(matrix1);          //freeing the callocs
    free_matrix2(matrix2);          //freeing the callocs
    if(i==0)
    {
        printf("NULL MATRIX!");
    }
    return 0;
}