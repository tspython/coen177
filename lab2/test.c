/*Sample C program for Lab assignment 1*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {

    printf("Parent PID: %d\n", getpid());

    if(fork() == 0){
        printf("Child1 PID: %d\n", getpid());
        for(int i = 0; i < 2; i++){
            if(fork() == 0){
                printf("Grandchild (From Child1): %d\n", getpid());
                exit(0);
            }
            wait(1000);
        }
        exit(0);
    }

    if(fork() == 0){
        printf("Child2 PID: %d\n", getpid());
        for(int i = 0; i < 2; i++){
            if(fork() == 0){
                printf("Grandchild (From Child2): %d\n", getpid());
                exit(0);
            }
        }
        wait(1000);
    }
    exit(0);
}
