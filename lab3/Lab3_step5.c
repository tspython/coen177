/* # Name: Tushar Shrivastav  */
/* # Date: Friday 2:15  */
/* # Title: Lab3 - Step 5 */
/* # Description: Below... */

/* In Computer Science, the producer–consumer problem is a classic multi- process synchronization */
/* example. The producer and the consumer share a common fixed-size buffer. The producer puts */
/* messages to the buffer while the consumer removes messages from the buffer. Pipes provide a perfect */
/* solution to this problem because of their built-in synchronization capability. So as a programmer, you do */
/* not have to worry about whether or not the buffer is empty or full to produce or consume messages. */
/* Write a C program to implement the producer-consumer message communication using pipes. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

void producer(int write_fd) {
    char buff[BUFFER_SIZE] = "Hello World - From Santa Clara University, CA"; // Initialize buffer with some data
    printf("Producer produced: %s\n", buff);
    write(write_fd, buff, BUFFER_SIZE);
    usleep(10);
    //exit(0);
}

void consumer(int read_fd) {
    char buff[BUFFER_SIZE];
    while (read(read_fd, buff, BUFFER_SIZE) > 0) printf("Consumer consumed: %s\n", buff);
}

int main(int argc, char *argv[]) {
    int fds[2];
    pipe(fds);

    if (fork() == 0) {
        printf("\nProducer on the upstream end of the pipe -> %d arguments\n", argc);
        close(fds[0]);
        producer(fds[1]);
    } else if (fork() == 0) {
        printf("\nConsumer on the downstream end of the pipe\n");
        close(fds[1]);
        consumer(fds[0]);
    } else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
