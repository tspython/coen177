/*
# Name: Tushar Shrivastav
# Date: 1/19/2024
# Title: Lab2 - Step 5
# Description: use generative logic to create 7 processes including
# parent where each parent can only have 2 or 0 children
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    printf("parent pid: %d\n", getpid());

    if(fork() == 0){
        printf("child1 pid: %d, parent: %d\n", getpid(), getppid());
        for(int i = 0; i < 2; i++){
            if(fork() == 0){
                printf("grandchild from child1: %d, parent: %d\n", getpid(), getppid());
                exit(0);
            }
            while(wait(NULL) >0);
        }
        exit(0);
    }

    if(fork() == 0){
        printf("child2 pid: %d, parent: %d\n", getpid(), getppid());
        for(int i = 0; i < 2; i++){
            if(fork() == 0){
                printf("grandchild from child2: %d, parent: %d\n", getpid(), getppid());
                exit(0);
            }
        }
        while(wait(NULL) > 0);
    }
    return 0;
}
