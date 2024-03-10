#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define MAX_THREADS 64

typedef struct {
    char *input_file_path;
    int buffer_size;
} ThreadData;

void *copy_file(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    FILE *input_fp, *output_fp;
    input_fp = fopen(data->input_file_path, "rb");
    if (input_fp == NULL) {
        printf("Error opening input file.\n");
        pthread_exit(NULL);
    }

    char output_filename[100];
    sprintf(output_filename, "output_%lu.bin", pthread_self()); // Unique file name based on thread ID

    output_fp = fopen(output_filename, "wb");
    if (output_fp == NULL) {
        printf("Error opening output file.\n");
        fclose(input_fp);
        pthread_exit(NULL);
    }

    char *buffer = (char *)malloc(data->buffer_size);
    if (buffer == NULL) {
        printf("Error allocating memory for buffer.\n");
        fclose(input_fp);
        fclose(output_fp);
        pthread_exit(NULL);
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, data->buffer_size, input_fp)) > 0) {
        fwrite(buffer, 1, bytes_read, output_fp);
    }

    free(buffer);
    fclose(input_fp);
    fclose(output_fp);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file_path> <buffer_size> <num_threads>\n", argv[0]);
        return 1;
    }

    char *input_file_path = argv[1];
    int buffer_size = atoi(argv[2]);
    int num_threads = atoi(argv[3]);
    if (num_threads < 1 || num_threads > MAX_THREADS) {
        printf("Number of threads must be between 1 and %d.\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data;
    thread_data.input_file_path = input_file_path;
    thread_data.buffer_size = buffer_size;

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int i;
    for (i = 0; i < num_threads; ++i) {
        if (pthread_create(&threads[i], NULL, copy_file, (void *)&thread_data) != 0) {
            printf("Error creating thread %d.\n", i);
            return 1;
        }
    }

    for (i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for I/O with buffer size %d and %d threads: %f seconds\n", buffer_size, num_threads, cpu_time_used);

    return 0;
}

