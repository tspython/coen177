#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <string.h>
#include <pthread.h> // library to deal w/ threads in c

struct thread {
    char *name;
    int delay;
};

void *msg(void *arg) {
    int i;
    struct thread *t = (struct thread *)arg;

    for (i=0;i<100;i++) {

        (strcmp(t->name,"Parent")) ? printf("\t \t \t %s Thread %d\n", t->name ,i) : printf("%s Thread %d\n", t->name ,i);
        usleep(t->delay);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t parent, child;

    // n microseconds to input from keyboard for delay
    struct thread parent_thread = {"Parent", atoi(argv[1])};
    struct thread child_thread = {"Child", atoi(argv[1])};

    printf("\n Before threading\n");

    pthread_create(&parent, NULL, msg, (void *)&parent_thread); // Parent thread
    pthread_create(&child, NULL, msg, (void *)&child_thread); // Child process

    pthread_join(parent, NULL);
    pthread_join(child, NULL);

    return 0;
}
