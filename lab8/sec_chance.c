/* 
# Name: Tushar Shrivastav
 # Date: Friday 2:15
 # Title: Lab8
 # Description: Implmentation of Second Chance Algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    bool reference; 
} ref_page;

int main(int argc, char *argv[]) {
    int CACHE_SIZE = atoi(argv[1]);
    ref_page cache[CACHE_SIZE];
    char pageCache[100];

    int totalFaults = 0;
    int placeInArray = 0;

    for (int i = 0; i < CACHE_SIZE; i++) {
         cache[i].pageno = -1;
         cache[i].reference = false; 
    }

    while (fgets(pageCache, 100, stdin)) {
        int page_num = atoi(pageCache);
        bool foundInCache = false;

        for (int i = 0; i < CACHE_SIZE; i++) {
            if (cache[i].pageno == page_num) {
                foundInCache = true;
                cache[i].reference = true;                 
                break;
            }
        }

        if (!foundInCache) {
            printf("%d\n", page_num);
            totalFaults++;

            while (cache[placeInArray].reference) { 
                cache[placeInArray].reference = false;
                placeInArray = (placeInArray + 1) % CACHE_SIZE;
            }

            cache[placeInArray].pageno = page_num;
            placeInArray = (placeInArray + 1) % CACHE_SIZE;
        }
    }

    // printf("%d Total Page Faults\n", totalFaults);
    return 0;
}

