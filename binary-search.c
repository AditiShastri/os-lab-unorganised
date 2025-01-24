#include <stdio.h>
#define SIZE 10
void sort(int arr[], int n)
{
    int temp;
    for (int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
int binary_search(int arr[], int n, int key) //returns position at which it is found
{
    int l=0;
    int r=n-1;
    int mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(arr[mid]==key)
        {
            return mid;
        }
        else if(arr[mid]<key)
        {
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
    }
    return -1;
}

int main()
{
    int n,i,key;
    printf("n:\t");
    scanf("%d",&n);
    int arr[SIZE];
    for(i=0;i<n;i++)
    {
        printf("\n Element %d \t",i+1);
        scanf("%d",&arr[i]);
    }

    printf("Array is: \n");
    for(i=0;i<n;i++)
    {
        printf("%d\t",arr[i]);
    }
    sort(arr,n);

    printf("key:\t");
    scanf("%d",&key);

    printf("\n%d",binary_search(arr,n,key));



}



