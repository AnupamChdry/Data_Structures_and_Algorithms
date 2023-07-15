#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>


//Global Variables
double qarray[1000000];           //storing elements for quick sort
double marray[1000000];           //storing elements for merge sort
double imarray[1000000];          //storing elements for improved-merge sort
double merged_array[1000000];     //merged_array is the merged sorted array we get from merging two halves in merge function
long int arr[500][35];            //for storing the output time intervals and number of comparisons
long int comp=0;                  //number of comparisons
int k=0;

//Quick Sort Functions
int partition(int low, int high)
{
    double x=qarray[low];
    int i=high+1;
    for(int j=high ; j>low ; j--)
    {
        comp++;
        if(qarray[j]>=x)               //if the element is greater than x then send it to latter part of partition
        {
            i--;
            double temp=qarray[i];     //swap
            qarray[i]=qarray[j];
            qarray[j]=temp;
        }
    }
    double temp=qarray[i-1];           //swapping x into the partition
    qarray[i-1]=qarray[low];
    qarray[low]=temp;
    return i-1;
}

void quicksort(int low, int high)
{
    if(low<high)
    {
        int index=partition(low, high);
        quicksort(low, index-1);
        quicksort(index+1, high);
    }
}


//Merge Sort Functions
void merge(int low, int mid, int high)     //merging of two arrays parts into the merged_array where smaller element will come first
{
    int i=low, j=mid+1, k=0;
    while(i<=mid && j<=high)
    {
        if(marray[i]<marray[j])
        {
            merged_array[k]=marray[i];
            i++;
        }
        else
        {
            merged_array[k]=marray[j];
            j++;
        }
        k++;
        comp++;
    }
    while(i<=mid)
    {
        merged_array[k]=marray[i];
        k++;
        i++;
    }
    while(j<=high)
    {
        merged_array[k]=marray[j];
        k++;
        j++;
    }
}

void mergesort(int low, int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        mergesort(low, mid);
        mergesort(mid+1, high);
        merge(low, mid, high);
        for(int i=0 ; i<=high-low ; i++)     //pasting back the sorted part of the array into original one
        {
            marray[i+low]=merged_array[i];
        }
    }
}


//Improved-Merge Functions
void imerge(int low, int mid, int high)
{
    k=0;
    if(imarray[mid]<=imarray[mid+1])     //if the array is already sorted improved merge will return and this reduces the time spent
    {
        return;
    }
    int i=low, j=mid+1;
    while(i<=mid && j<=high)
    {
        if(imarray[i]<imarray[j])
        {
            merged_array[k]=imarray[i];
            i++;
        }
        else
        {
            merged_array[k]=imarray[j];
            j++;
        }
        k++;
        comp++;
    }
    while(i<=mid)     //if i<=mid then the elements in array are copied to merged_array then back to array in normal merge, here they are copied directly
    {                 
        imarray[high]=imarray[mid];
        high--;
        mid--;
    }                 //if j<=high then the elements in array are copied to merged_array then back to array in normal merge, here the integer k
}                     //will help specify how many elemnts of merged_array are to be copied back to array (this reduces time used when j<=high)

void imergesort(int low, int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        imergesort(low, mid);
        imergesort(mid+1, high);
        imerge(low, mid, high);
        for(int i=0 ; i<k ; i++)     //pasting the merged array into original one so that original part becomes sorted
        {
            imarray[i+low]=merged_array[i];
        }
    }
}


//Main Function
int main()
{
    srand((unsigned)time(NULL));
    int MAX_RANGE = 50, n=100, z=0;     //n=number of elements to be sorted, z= the index of arr where output will go
    clock_t t, time;
    while(n<=1000000)                   //for average running time and number of comparison of quick and merge sort
    {
        for(int i=0 ; i<500 ; i++)
        {
            for(int j=0 ; j<n ; j++)
            {
                marray[j] = ((double)rand()/(double)RAND_MAX)*MAX_RANGE;
                qarray[j]=marray[j];
                imarray[j]=marray[j];
            }
            comp=0;
            t=clock();
            mergesort(0, n-1);
            time=clock()-t;
            long int m_time=((double)time*1000000)/(double)CLOCKS_PER_SEC;     //time for merge sort
            arr[i][z]=m_time;
            arr[i][z+5]=comp;
            comp=0;
            t=clock();
            quicksort(0, n-1);
            time=clock()-t;
            long int q_time=((double)time*1000000)/(double)CLOCKS_PER_SEC;     //time for quick sort
            arr[i][z+10]=q_time;
            arr[i][z+15]=comp;
            comp=0;
            t=clock();
            imergesort(0, n-1);
            time=clock()-t;
            long int im_time=((double)time*1000000)/(double)CLOCKS_PER_SEC;     //time for improved merge sort
            arr[i][z+20]=im_time;
            arr[i][z+25]=comp;
        }
        z++;
        n*=10;
    }
    n=100000;
    z=30;
    while(n<=1000000)     //for time complexity of quick sort
    {
        for(int i=0 ; i<500 ; i++)
        {
            for(int j=0 ; j<n ; j++)
            {
                qarray[j] = ((double)rand()/(double)RAND_MAX)*MAX_RANGE;
            }
            comp=0;
            t=clock();
            quicksort(0, n-1);
            time=clock()-t;
            long int time_interval=((double)time*1000000)/(double)CLOCKS_PER_SEC;
            arr[i][z]=time_interval;
        }
        z++;
        n+=200000;
    }
    FILE *fptr;
    fptr=fopen("E:\\eso207\\values.csv","a+");     //output directed to this file
    for(int i=0 ; i<500 ; i++)
    {
        for(int j=0 ; j<35 ; j++)
        {
            fprintf(fptr, "%ld,", arr[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    return 0;
}