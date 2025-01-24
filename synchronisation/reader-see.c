#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
sem_t writer_lock,mutex;
int reader_count=0,page_count=0;

void * writer(void * writer_no)
{
    int n=*((int*)writer_no);
    sem_wait(&writer_lock);
    page_count++; //this is the resource that writer creates
    printf("Writer %d is writing page %d\n",n,page_count);
    sem_post(&writer_lock);

}

void * reader(void * reader_no)
{
    int n=*((int*)reader_no);

    //first reader acquires mutex and fills his attendence by incrementing reader page_count
    sem_wait(&mutex);
    reader_count++;
    sem_post(&mutex);

    //if you are the first reader, you must block writers 
    if(reader_count==1)
    {
        sem_wait(&writer_lock);
    }

    //now you read
    printf("Reader %d is Reading page %d\n",n,page_count);

    //you exit the place by siging against your attendence again
    sem_wait(&mutex);
    reader_count--;
    sem_post(&mutex);

    //if you are the last reader, you now allow writers
     if(reader_count==0)
    {
        sem_post(&writer_lock);
    }

}
int main()
{
    sem_init(&writer_lock,0,1);
    sem_init(&mutex,0,1);

    int pages[6]={1,2,3,1,2,3};

    pthread_t reader_threads[3],writer_threads[3];
    for(int i=0;i<3;i++)
    {
        pthread_create(&writer_threads[i],NULL,&writer,(void *)&pages[i]);
    }
    for(int i=3;i<6;i++)
    {
        pthread_create(&reader_threads[i],NULL,&reader,(void *)&pages[i]);
    }
    for(int i=0;i<3;i++)
    {
        pthread_join(writer_threads[i],NULL);
    }
    for(int i=3;i<6;i++)
    {
        pthread_join(reader_threads[i],NULL);
    }
    return 0;
}
