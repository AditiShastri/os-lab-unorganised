#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 10

sem_t full,empty;
pthread_mutex_t mutex;
int counter; //number of filled spots in buffer
int buffer[SIZE];

void write(int item)
{
    buffer[++counter]=item;
}


int read()
{
    return buffer[counter--];
}

void* producer (void* p)
{
    int item=rand()%5; //item to be inserted into buffer

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    write(item);
    printf("producer has produced item %d",item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    
}
void* consumer(void* p)
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    int item=read();
    printf("consumer has consumed item %d",item);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}
int main()
{   
    sem_init(&full,0,0);
    sem_init(&empty,0,SIZE);
    counter=0;

    int n1,n2;
    printf("\nEnter the no of producers: ");
    scanf("%d",&n1);
    printf("\nEnter the no of consumers: ");
    scanf("%d",&n2);

    pthread_t producers[SIZE],consumers[SIZE];

    int i;
    for(i=0;i<n1;i++)
    {
        pthread_create(&producers[i],NULL,&producer,NULL);
    }
    for(i=0;i<n2;i++)
    {
        pthread_create(&consumers[i],NULL,&consumer,NULL);
    }

     for(i=0;i<n1;i++)
    {
        pthread_join(producers[i],NULL);
    }
    for(i=0;i<n2;i++)
    {
        pthread_join(consumers[i],NULL);
    }

    return 0;
    


}