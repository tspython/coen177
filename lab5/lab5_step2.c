//  # Name : Tushar Shrivastav
//  # Date : 2/9/2024
//  # Title: Lab1: Step 2
//  # Description: Modify code in step 1 for using mutex locks instead of what was there originally.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
//sem_t *mutex;
pthread_mutex_t mutex;

void* go(void* arg) {
  pthread_mutex_lock(&mutex);
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section
  sleep(1);
  pthread_mutex_unlock(&mutex); //exit section
  return (NULL);
}

int main() {
  //mutex = sem_open("mutex", O_CREAT, 0644, 1);
  pthread_mutex_init(&mutex, NULL);
  static int i;
  for (i = 0; i < NTHREADS; i++)
    pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i],NULL);
    printf("\t\t\tThread %d returned \n", i);
  }
  printf("Main thread done.\n");
  pthread_mutex_destroy(&mutex);
  return 0;
}
