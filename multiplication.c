#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

#define SIZE 4
int a[SIZE][SIZE],b[SIZE][SIZE];


void* row_multiply(void* row)
{
    int n=*((int*)row); //n is row number in integral form


    for(int i=0;i<SIZE;i++)
    {
        b[n][i]=a[n][i];
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            b[n][i]*=a[n][i];
        }
    }

}


int main()
{
    printf("Enter the matrix of size 4x4:\n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("Element [%d][%d]\t",i+1,j+1);
            scanf("%d",&a[i][j]);
        }
        
    }
    printf("\nMatrix A is:\n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("Element [%d][%d]=%d\t",i+1,j+1,a[i][j]);
        }
        printf("\n");
    }

    pthread_t threads[SIZE];
    for(int i=0;i<SIZE;i++)
    {
        int* row=(int*)malloc(sizeof(int));
        *row=i;
        //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
        pthread_create(&threads[i] ,NULL,&row_multiply,(void*) row); //all args are pointers
    }

    for(int i=0;i<SIZE;i++)
    {
        
        pthread_join(threads[i],NULL);
    }

    printf("\nMatrix B is:\n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("Element [%d][%d]=%d\t",i+1,j+1,b[i][j]);
        }
        printf("\n");
    }

    pthread_exit(NULL);
    return(0);

}
