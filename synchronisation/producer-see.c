#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h> //for rand()
#define MAXPRODUCERS 20
#define MAXCONSUMERS 20
#define BUFFERSIZE 10

//we need 1 mutex and 2 semaphores
int counter=-1;
pthread_mutex_t mutex;


sem_t empty,full;

int buffer[BUFFERSIZE];

void * producer(void * arg) //even tho we aint giving anything in this, we must follow format for pthreads
{
    sem_wait(&empty);//producer waits for an empty slot in the buffer
    pthread_mutex_lock(&mutex);
    int item=rand()%5;
    buffer[++counter]=item;
    printf("\nProducer has produced item: %d\n", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void * consumer(void * arg)
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    int item=buffer[counter--];
    printf("\nConsumer has consumed item: %d\n", item);
    //printf("%d",item_received);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

}


int main()
{
    pthread_mutex_init(&mutex,NULL); 
    sem_init(&empty,0,BUFFERSIZE);
    sem_init(&full,0,0);

    int prod_no,cons_no;
    printf("Enter no of Producers:\t");
    scanf("%d",&prod_no);
    printf("Enter no of Consumers:\t");
    scanf("%d",&cons_no);

//pehle pthead create, phire join, phir exit
    pthread_t producer_threads[MAXPRODUCERS],consumer_threads[MAXCONSUMERS];
    for(int i=0;i<prod_no;i++)
    {
        pthread_create(&producer_threads[i],NULL,&producer,NULL);
    }
     for(int i=0;i<cons_no;i++)
    {
        pthread_create(&consumer_threads[i],NULL,&consumer,NULL);
    }
    for(int i=0;i<prod_no;i++)
    {
        pthread_join(producer_threads[i],NULL);
    }
     for(int i=0;i<cons_no;i++)
    {
        pthread_join(consumer_threads[i],NULL);
    }
    pthread_exit(NULL);



    return 0;
}