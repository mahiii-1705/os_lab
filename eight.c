Code:
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // number of philosophers

sem_t mutex;
sem_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    sem_wait(&mutex);
    printf("Philosopher %d is thinking.\n", id);
    sem_post(&mutex);

    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id+1)%N]);

    sem_wait(&mutex);
    printf("Philosopher %d is eating.\n", id);
    sem_post(&mutex);

    sleep(1);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id+1)%N]);

    sem_wait(&mutex);
    printf("Philosopher %d finished eating and left chopsticks.\n", id);
    sem_post(&mutex);

    return NULL;
}

int main() {
    int i;
    pthread_t tid[N];
    int phil[N];

    sem_init(&mutex, 0, 1);
    for(i=0;i<N;i++)
        sem_init(&chopstick[i], 0, 1);

    for(i=0;i<N;i++) {
        phil[i]=i;
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    for(i=0;i<N;i++)
        pthread_join(tid[i], NULL);

    for(i=0;i<N;i++)
        sem_destroy(&chopstick[i]);
    sem_destroy(&mutex);

    return 0;
}