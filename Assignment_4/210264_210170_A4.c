#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct node
{
    int value, height;
    struct node *left, *right;
};
int i=0;
struct node *arr[10000000];     //stores the ex-nearly balanced subtree while making it perfectly balanced
double time_mul[200];              //storing time of first i iterations where i is multiple of 5*10^4
double time_ith[899998];        //storing time for iᵗʰ iteration for i in (10^5, 10^6)

int max(int a, int b)           //returns maximum of two numbers
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int height(struct node *root)                     //returns height of the node (leaf nodes are at height 1)
{
    if(root==NULL)
    {
        return 0;
    }
    else if(root->left==NULL && root->right!=NULL)
    {
        return 1+root->right->height;
    }
    else if(root->left!=NULL && root->right==NULL)
    {
        return 1+root->left->height;
    }
    else if(root->left==NULL && root->right==NULL)
    {
        return 1;
    }
    else
    {
        return 1+max(root->left->height, root->right->height);
    }
}

struct node *tree_to_arr(struct node *root)           //recursive function for storing the ex-nearly balanced sub tree in arr
{                                                     //(i keeps track of the number of nodes in the subtree)
    if(root->left!=NULL)
    {
        root->left=tree_to_arr(root->left);
    }
    arr[i]=root;
    i++;
    if(root->right!=NULL)
    {
        root->right=tree_to_arr(root->right);
    }
    return root;
}

struct node *arr_to_perfect_tree(int low, int high)    //recursive function to make the subtree perfectly balanced
{
    if(low>high)
    {
        return NULL;
    }
    arr[(high+low)/2]->left=arr_to_perfect_tree(low, -1+(low+high)/2);
    arr[(high+low)/2]->right=arr_to_perfect_tree(1+(low+high)/2, high);
    arr[(high+low)/2]->height=height(arr[(high+low)/2]);
    return arr[(high+low)/2];
}

struct node *insert(struct node *root, int val)   //function for inserting the node
{
    if(root==NULL)
    {
        struct node *temp=(struct node *)calloc(1, sizeof(struct node));
        temp->value=val;
        temp->height=1;
        return temp;
    }
    if(root->value>val)
    {
        root->left=insert(root->left, val);
    }
    else if(root->value<val)
    {
        root->right=insert(root->right, val);
    }
    root->height=height(root);
    if(3*(root->height)>4*height(root->right) || 3*(root->height)>4*height(root->left))    //checking if nearly balanced 
    {
        i=0;
        root=tree_to_arr(root);
        i--;
        root=arr_to_perfect_tree(0, i);
    }
    return root;
}

void close(struct node *root)        //recursive function for freeing the tree at the end
{
    if(root->left!=NULL)
    {
        close(root->left);
    }
    if(root->right!=NULL)
    {
        close(root->right);
    }
    free(root);
}

int main()
{
    clock_t start_t, end_t;
    double total_t, ith_t;
    struct node *root=NULL;
    int n=1;
    start_t=clock();
    for(int i=1 ; i<=10000000 ; i++)
    {
        if(i>100000 && i<1000000)            //in this if end_t will be considered as starting time for insertion
        {                                    //and the ending time will be taken directly
            end_t=clock();
            root=insert(root, i);
            time_ith[i-100000]=(double)(clock()-end_t);
        }
        else
        {
            root=insert(root, i);
        }
        if(i==n*50000)
        {
            end_t=clock();            //end time of first i iterations
            time_mul[n-1]=(double)(end_t-start_t);
            n++;
        }
    }
    FILE* fp1 = fopen("E:\\eso207\\fp1.csv", "w+");    //files where the data will be stored
    FILE* fp2 = fopen("E:\\eso207\\fp2.csv", "w+");
    for(int i=0 ; i<200 ; i++)
    {
        fprintf(fp1, "%lf\n", time_mul[i]);
    }
    for(int i=0 ; i<899998 ; i++)
    {
        fprintf(fp2, "%lf\n", time_ith[i]);
    }
    fclose(fp1);
    fclose(fp2);
    close(root);
    return 0;
}