#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#define SIZE 4

int A[SIZE][SIZE];
int B[SIZE][SIZE];

//for pthread to execute
//function should be of form
//(void*)function(*arg);

void* row_multiply(void*row) //brackets used only for typecast. here not needed
{
    int row_no=*((int*)row);
    for(int i=0;i<SIZE;i++)//copying contents row row_no of matA to matB
    {
        B[row_no][i]= A[row_no][i];
    }

    for(int i=0;i<SIZE;i++)
    {
        for(int j=1;j<row_no+1;j++) //raising each entry in B[row_no] by row_no+1
        {
             B[row_no][i]*= A[row_no][i];     
        }
    }

}

int main()
{
    //enter matA
    printf("Matrix A:\n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("Element [%d][%d]L\t",i+1,j+1);
            scanf("%d",&A[i][j]);
        }
        
    }

    //print matA
    printf("Matrix A is : \n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("Element [%d][%d]:\t %d",i+1,j+1,A[i][j]);
            printf("\n");
        }
        
    }

    //create threads
    pthread_t threads[SIZE];
    for(int i=0;i<SIZE;i++)
    {
        //create a value row_no that is gloval and not on stakc; to ensure that value passed to each thread is unique and correct
        //value stored in row_no=iteration number i
        int* row_no=(int*)malloc(sizeof(int));
        *row_no=i;

        pthread_create(&threads[i],NULL,&row_multiply,(void*)row_no); //all inputs are pointers
    }

    //print matB
    printf("Matrix B is : \n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("Element [%d][%d]:\t: %d",i+1,j+1,B[i][j]);
            printf("\n");
        }
        
    }


    //join all the threads in a loop
    for(int i=0;i<SIZE;i++)
    {
        pthread_join(threads[i],NULL); 
    }
    pthread_exit(NULL);
    return 0;


}