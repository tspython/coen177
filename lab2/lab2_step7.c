/*
# Name: Tushar Shrivastav
# Date: 1/19/2024
# Title: Lab2 - Step 7
# Description: modify example code to have the child process called execlp and execute
# the UNIX list (ls) command
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

int main(int argc, char *argv[]) {
    pid_t  pid;
    printf("\n Before forking.\n");
    pid = fork();

    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
   // Child process
    else if(pid == 0)  {
        execlp("/bin/ls", "ls", NULL);
    }
    else {
        wait(NULL);
        printf("Child complete");
        exit(0);
    }
    return 0;
}
