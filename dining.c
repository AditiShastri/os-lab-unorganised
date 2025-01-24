#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define N 5
#define LEFT (phnum+4)%5
#define RIGHT (phnum+1)%5
#define THINKING 2
#define HUNGRY 1
#define EATING 0

sem_t forks[5],mutex;
int state[5];

void test(int phnum)
{
    if(state[phnum]==HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[phnum]=EATING;
        sleep(1);
        printf("Philosopher %d takes fork %d and %d\n",phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        sem_post(&forks[phnum]);

    }
}

void put_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum]=THINKING;
    printf("Philosopher %d puts down fork %d and %d\n",phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void take_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum]=HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phnum);
    sem_post(&mutex);
    sem_wait(&forks[phnum]);

}




void* philosopher(void* phnum)
{
    while(1)
    {
        int i=*((int *) phnum);
        sleep(1);
        take_fork(i);
        put_fork(i);
    }
}



int main()
{
    int i;
    int philosophers[5]={1,2,3,4,5};
    for(i=0;i<5;i++)
    {
        sem_init(&forks[i],0,1);
    }
    sem_init(&mutex,0,1);

    pthread_t threads[5];

    for(i=0;i<5;i++)
    {
        pthread_create(&threads[i],NULL,&philosopher,&philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

       for(i=0;i<5;i++)
    {
        pthread_join(threads[i],NULL);
    }


}
