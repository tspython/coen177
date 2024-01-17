#include <stdio.h>
#include <unistd.h>

#define MAX_PROCESSES 7

// Static array to store process numbers
static int processNumbers[MAX_PROCESSES] = {1, 2, 3, 4, 5, 6, 7};

void createProcesses(int level, int maxLevel) {
    if (level < maxLevel) {
        for (int i = 0; i < 2; ++i) {
            if (fork() == 0) {
                // Child process
                printf("Process #%d at level %d\n", processNumbers[level], level);
                createProcesses(level + 1, maxLevel);
                return;
            }
        }
    }

    // Parent process or termination condition
    printf("Process #%d at level %d\n", processNumbers[level], level);
}

int main() {
    createProcesses(0, 3);  // Change 3 to adjust the level

    return 0;
}
