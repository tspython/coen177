//  # Name : Tushar Shrivastav
//  # Date : 2/9/2024
//  # Title: Lab1: Step 3
//  # Description: Solving Producer and Consumer problem using semaphores. Please see below for implementation.

//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1
//Producer thread

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

sem_t full, empty, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
  int msg_item = 0;
  while(1) {
    msg_item++;

    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[in] = msg_item;
    in = (in + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);

    printf("Producer produced: %d\n", msg_item);
    sleep(rand()%3);
  }
}

void *consumer(void *arg) {
  int msg_item;
  while(1) {

    sem_wait(&full);
    sem_wait(&mutex);

    msg_item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&empty);

    printf("Consumer consumed: %d\n", msg_item);
    sleep(rand()%3);
  }
}

int main(){
   pthread_t producer_thread, consumer_thread;

   sem_init(&full, 0, 0);
   sem_init(&empty, 0, BUFFER_SIZE);
   sem_init(&mutex, 0, 1);

   pthread_create(&producer_thread, NULL, producer, NULL);
   pthread_create(&consumer_thread, NULL, consumer, NULL);

   pthread_join(producer_thread, NULL);
   pthread_join(consumer_thread, NULL);

   sem_destroy(&full);
   sem_destroy(&empty);
   sem_destroy(&mutex);

   return 0;
}
