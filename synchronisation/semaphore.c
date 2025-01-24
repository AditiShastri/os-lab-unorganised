#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t mySemaphore;
int sharedResource = 0;

void* threadFunction(void* arg) {
    // Wait (lock) the semaphore
    sem_wait(&mySemaphore);
    // Critical section
    sharedResource++;
    printf("Shared Resource: %d\n", sharedResource);
    // Post (unlock) the semaphore
    sem_post(&mySemaphore);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    // Initialize the semaphore with a value of 1
    sem_init(&mySemaphore, 0, 1);
    pthread_create(&thread1, NULL, threadFunction, NULL);
    pthread_create(&thread2, NULL, threadFunction, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    // Destroy the semaphore
    sem_destroy(&mySemaphore);
    return 0;
}
