#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CACHE_SIZE 2 // Minimum cache size allowed

typedef struct {
    int pageno;
} ref_page;

int main(int argc, char *argv[]) {
    int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    if (CACHE_SIZE < MIN_CACHE_SIZE) {
        fprintf(stderr, "Error: Cache size must be at least %d\n", MIN_CACHE_SIZE);
        return 1;
    }
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int front = 0; // Pointer to the first element in the cache
    int rear = 0;  // Pointer to the next available position in the cache

    for (i = 0; i < CACHE_SIZE; i++) {
        cache[i].pageno = -1; // Initialize cache
    }

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache); // Stores number read from file as an int

        // Check if page is already in cache
        int pageFound = 0;
        for (i = 0; i < CACHE_SIZE; i++) {
            if (cache[i].pageno == page_num) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) { // Page fault
            totalFaults++;
            if (rear < CACHE_SIZE) {
                cache[rear].pageno = page_num;
                rear++;
            } else {
                // Replace the oldest page (FIFO)
                cache[front].pageno = page_num;
                front = (front + 1) % CACHE_SIZE; // Move front pointer circularly
            }
        }
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;
}
