#include <stdio.h>
#include <unistd.h>

/*
** forks new processes until desired depth in process tree
** limiting child processes to two each
*/
void newProcess(int, int);

int main() {
    newProcess(0, 7); // (2^3) - 1 = 7 (we are including parent process)
    return 0;
}

void newProcess(int pNum, int tP) {
    if(pNum >= tP) return;
    printf("Process: %d\n", pNum);

    int i;
    for(i = 0; i < 2; i++) {
        if(fork() == 0) {
            newProcess(pNum * 2 + i + 1, tP);
            break;
        }
    }
}
