#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file_path> <buffer_size>\n", argv[0]);
        return 1;
    }

    char buffer[100000];
    FILE *fp;
    clock_t start, end;
    double cpu_time_used;

    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int buffer_size = atoi(argv[2]);
    size_t bytes_read;
    start = clock();
    while ((bytes_read = fread(buffer, 1, buffer_size, fp)) > 0) {
        // Do something with the data in the buffer
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for I/O with buffer size %d: %f seconds\n", buffer_size, cpu_time_used);

    fclose(fp);

    return 0;
}

