#include<stdio.h>
    #include<semaphore.h>
    #include<pthread.h>
    #include<stdlib.h>
    #define buffersize 10
    
    pthread_mutex_t mutex;
    pthread_t tidP[20],tidC[20];//producers,consumers
    sem_t full,empty;//semaphores to control full/empty state in buffer
    int counter;//track no. of items in buffer
    int buffer[buffersize];
    
    //Initialize semaphores and mutex variables
    void initialize(){
    pthread_mutex_init(&mutex,NULL);
    sem_init(&full,0,0);
    sem_init(&empty,0,buffersize);
    counter=0;
    }
     
    void write(int item){
      buffer[counter++]=item;
    }
    int read(){
      return(buffer[--counter]);
    }
    //Producer process
    void * producer (void * param){
    int waittime,item,i;
    item=rand()%5;
    
    sem_wait(&empty); //if buffer is full, producer waits, by decrementing empty
    pthread_mutex_lock(&mutex); //mutual exclusion to write to buffer
    printf("\nProducer has produced item: %d\n",item);
    write(item);
    pthread_mutex_unlock(&mutex); //unlock mutex
    sem_post(&full); //increments full, indicating new item added to buffer
    }
    
    //Consumer process
    void *consumer (void * param){
    int waittime,item;
    
    sem_wait(&full);//if buffer is empty, consumer waits
    pthread_mutex_lock(&mutex); //mutual exclusion to write to buffer
    item=read();
    printf("\nConsumer has consumed item: %d\n",item);
    pthread_mutex_unlock(&mutex); //unlock mutex
    sem_post(&empty);//increments empty, indicating buffer is no longer full
    }
    
    int main(){
    int n1,n2,i;
    initialize();
    printf("\nEnter the no of producers: ");
    scanf("%d",&n1);
    printf("\nEnter the no of consumers: ");
    scanf("%d",&n2);
    for(i=0;i<n1;i++)
      pthread_create(&tidP[i],NULL,producer,NULL);
    for(i=0;i<n2;i++)
      pthread_create(&tidC[i],NULL,consumer,NULL);
    
    for(i=0;i<n1;i++)
      pthread_join(tidP[i],NULL);
    for(i=0;i<n2;i++)
      pthread_join(tidC[i],NULL);
    
    exit(0);
    }