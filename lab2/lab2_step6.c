/*
# Name: Tushar Shrivastav
# Date: 1/19/2024
# Title: Lab2 - Step 6
# Description: modify example code to use pthread and use pthread_create to emulate
# behavior of example code by passing msg() function and delay
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

struct thread {
    char *name;
    int delay;
};

void *msg(void *arg) {
    int i;
    struct thread *t = (struct thread *)arg;

    for (i = 0; i < 100; i++) {
        (strcmp(t->name, "Parent")) ? printf("\t \t \t %s Thread %d\n", t->name, i) : printf("%s Thread %d\n", t->name, i);
        usleep(t->delay);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t parent, child;
    int status;

    // n microseconds to input from keyboard for delay
    struct thread parent_thread = {"Parent", atoi(argv[1])};
    struct thread child_thread = {"Child", atoi(argv[1])};

    printf("\n Before threading\n");

    if ((status = pthread_create(&parent, NULL, &msg, (void *)&parent_thread)) != 0) {
        fprintf(stderr, "Error creating parent thread: %s\n", strerror(status));
        exit(EXIT_FAILURE);
    }

    if ((status = pthread_create(&child, NULL, &msg, (void *)&child_thread)) != 0) {
        fprintf(stderr, "Error creating child thread: %s\n", strerror(status));
        exit(EXIT_FAILURE);
    }

    if ((status = pthread_join(parent, NULL)) != 0) {
        fprintf(stderr, "Error joining parent thread: %s\n", strerror(status));
        exit(EXIT_FAILURE);
    }

    if ((status = pthread_join(child, NULL)) != 0) {
        fprintf(stderr, "Error joining child thread: %s\n", strerror(status));
        exit(EXIT_FAILURE);
    }

    return 0;
}
