#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// output FIFO:  9515
//

typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
    int CACHE_SIZE = atoi(argv[1]);
    ref_page cache[CACHE_SIZE];
    char pageCache[100];

    int i;
    int totalFaults = 0;

    int placeInArray = 0;

    for (i = 0; i < CACHE_SIZE; i++){
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
        int page_num = atoi(pageCache);
        bool foundInCache = false;
        for (i=0; i< CACHE_SIZE; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                break;
            }
        }
        if (foundInCache == false){
            totalFaults++;
            printf("Page fault for page: %d, inserting at index: %d, causing total faults to increase to: %d\n", page_num, placeInArray, totalFaults);

            cache[placeInArray].pageno = page_num;
            placeInArray = (placeInArray + 1) % CACHE_SIZE;
        }

    }

    //printf("%d Total Page Faults\n", totalFaults);
    return 0;
}
