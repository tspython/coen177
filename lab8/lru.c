#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int counter; 
} ref_page;

int main(int argc, char *argv[]) {
    int CACHE_SIZE = atoi(argv[1]);
    ref_page cache[CACHE_SIZE];
    char pageCache[100];

    int i;
    int totalFaults = 0;
    int placeInArray = 0;
    int time = 0;     for (i = 0; i < CACHE_SIZE; i++) {
        cache[i].pageno = -1;
        cache[i].counter = 0;
    }

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);
        bool foundInCache = false;
        for (i = 0; i < CACHE_SIZE; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                cache[i].counter = time++; 
                break;
            }
        }
        if (foundInCache == false) {
            totalFaults++;
                        printf("%d\n",page_num); 

            int lruIndex = 0;
            for (i = 1; i < CACHE_SIZE; i++) {
                if (cache[i].counter < cache[lruIndex].counter) {
                    lruIndex = i;                
                }
            }
            printf(stderr,"Page fault for page: %d. Replacing LRU page in index: %d with last used time: %d. Total page faults so far: %d\n", page_num, lruIndex, time, totalFaults);
            cache[lruIndex].pageno = page_num; 
            cache[lruIndex].counter = time++;         
        }
    }

    // printf("%d Total Page Faults\n", totalFaults);
    return 0;
}

