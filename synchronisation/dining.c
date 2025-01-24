#include <pthread.h>
    #include <semaphore.h>
    #include <stdio.h>
    #include<unistd.h>
    #define N 5  //number of philosophers
    #define THINKING 2  //defining states of philosophers
    #define HUNGRY 1
    #define EATING 0
    #define LEFT (phnum + 4) % N 
    #define RIGHT (phnum + 1) % N
    
    int state[N];
    int phil[N] = { 0, 1, 2, 3, 4 }; //ID of philosophers
    sem_t mutex, S[N]; //sempahores to control synchronisation
    
    //check if neighbours are eating
    void test(int phnum){ 
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
    state[phnum] = EATING; //change state to eating
    sleep(2);
    printf("Philosopher %d takes fork %d and %d\n",phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is Eating\n", phnum + 1);
    sem_post(&S[phnum]);// used to wake up hungry philosophers during putfork
    }
    } 
    
    // take up chopsticks
    void take_fork(int phnum){
    sem_wait(&mutex);//only one philosopher can change state at a time
    state[phnum] = HUNGRY;// change state to hungry
    printf("Philosopher %d is Hungry\n", phnum + 1);
    //eat if neighbours are not eating
    test(phnum);
    sem_post(&mutex);
    sem_wait(&S[phnum]);//if unable to eat wait to be signalled
    sleep(1);
    }
    
    // put down chopsticks
    void put_fork(int phnum){
    sem_wait(&mutex);
    state[phnum] = THINKING;//change state to thinking
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    //if neigbours can start eating
    test(LEFT); 
    test(RIGHT);
    sem_post(&mutex);//
    }
    
    //thread calling function
    void* philospher(void* num){
    while (1) {
    int* i = num;
    sleep(1);//time spent thinking before eating again
    take_fork(*i);//decide to eat again
    sleep(0);
    put_fork(*i);//finish eating
    }
    }
    
    int main(){
    int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
     sem_init(&S[i], 0, 0);
    
    for (i = 0; i < N; i++) {
    // create philosopher process threads
     pthread_create(&thread_id[i], NULL, philospher, &phil[i]);
     printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++)
     pthread_join(thread_id[i], NULL);
    
    }