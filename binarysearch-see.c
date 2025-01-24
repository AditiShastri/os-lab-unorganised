#include <stdio.h>
#define SIZE 10
//no need for pointers for sort, as array is sorted and globally ho jata hai

void sort(int arr[SIZE], int n) //selection sort
{
    int min_index,temp;
    for(int i=0;i<n-1;i++)
    {
        min_index=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[j]<arr[min_index])
            {
                min_index=j;
            }
            
        }
        if(min_index!=i)
        {
            temp=arr[min_index];
            arr[min_index]=arr[i];
            arr[i]=temp;
        }
    }
}

int binarysearch(int arr[SIZE], int n, int key) //returns pos at which found, -1 if not found
{
    int mid,l,r;
    l=0;
    r=n-1;

    while(l<=r)
    {
        mid=(l+r)/2;
        if(arr[mid]==key)
        {
            return mid;
        }
        else if(arr[mid]>key)
        {
            r=mid-1;
        }
        else
        {
            l=mid+1;
        }
    }
    return -1;
}

int main()
{
    int n,arr[SIZE],key;
    printf("n:\t");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("Element %d:\t",i+1);
        scanf("%d",&arr[i]);
    }

    printf("\nkey:\t");
    scanf("%d",&key);

    int res=binarysearch(arr,n,key);
    if(key==-1)
    {
        printf("\n Not found\n");
    }
    else{
        printf("\n Found at %d\n",res);
    }
    return 0;
}