//  # Name : Tushar Shrivastav
//  # Date : 2/9/2024
//  # Title: Lab1: Step 3
//  # Description: Solving Producer and Consumer problem using condition variables. Please see below for implementation.

#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 10

pthread_cond_t full_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void *producer(void *arg) {
    int msg_item = 0;
    while(1) {
        msg_item++;

        pthread_mutex_lock(&mutex);
        while ((in + 1) % BUFFER_SIZE == out) {
            pthread_cond_wait(&empty_cond, &mutex);
        }

        buffer[in] = msg_item;
        in = (in + 1) % BUFFER_SIZE;

        pthread_cond_signal(&full_cond);
        pthread_mutex_unlock(&mutex);

        printf("Producer produced: %d\n", msg_item);
        sleep(rand()%3);
    }
}

void *consumer(void *arg) {
    int msg_item;
    while(1) {
        pthread_mutex_lock(&mutex);
        while (in == out) {
            pthread_cond_wait(&full_cond, &mutex);
        }

        msg_item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        pthread_cond_signal(&empty_cond);
        pthread_mutex_unlock(&mutex);

        printf("Consumer consumed: %d\n", msg_item);
        sleep(rand()%3);
    }
}

int main(){
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
