#include <stdio.h>
#include <unistd.h>

void newProcess(int, int);

int main() {
    newProcess(0, 7);
    return 0;
}

void newProcess(int pNum, int tP) {
    if(pNum >= tP) return;
    pid_t pid = getpid();
    printf("Process: %d, PID: %d\n", pNum, pid);
    fflush(stdout);

    int i;
    for(i = 0; i < 2; i++) {
        if(fork() == 0) {
            newProcess(pNum * 2 + i + 1, tP);
            break;
        }
    }
    while(wait(NULL) > 0);
}
