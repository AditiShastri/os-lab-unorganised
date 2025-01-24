#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


sem_t mutex,wrt;
int rcount,count;

void* writer(void *p)
{
    int i=*((int*)p);
    sem_wait(&wrt);
    printf("\n writer %d writes to page number %d\n",i,++count);
    sem_post(&wrt);

}

void* reader(void* p)
{
    int i=*((int*)p);
    sem_wait(&mutex);
    rcount++;
    if(rcount==1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    
    printf("\n reader %d reads page number %d\n",i,count);

    sem_wait(&mutex);
    rcount--;
    if(rcount==0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
}


int main()
{
    pthread_t threads[6];
    int a[6]={1,2,3,1,2,3};
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);
    int i;
    for(i=0;i<3;i++)
    {
        pthread_create(&threads[i],NULL,&writer,&a[i]);
    }
    for(i=3;i<6;i++)
    {
        pthread_create(&threads[i],NULL,&reader,&a[i]);
    }
    for(i=0;i<6;i++)
    {
        pthread_join(threads[i],NULL);
    }
    return 0;

}