#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file_path> <buffer_size>\n", argv[0]);
        return 1;
    }

    FILE *input_fp, *output_fp;
    clock_t start, end;
    double cpu_time_used;

    input_fp = fopen(argv[1], "rb");
    if (input_fp == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    int buffer_size = atoi(argv[2]);
    char buffer[buffer_size];
    size_t bytes_read;

    start = clock();

    // Loop until end of input file
    while ((bytes_read = fread(buffer, 1, buffer_size, input_fp)) > 0) {
        // Open a new file for writing
        char output_filename[100];
        sprintf(output_filename, "output_%zu.bin", ftell(input_fp)); // Unique file name based on position in input file
        output_fp = fopen(output_filename, "wb");
        if (output_fp == NULL) {
            printf("Error opening output file.\n");
            fclose(input_fp);
            return 1;
        }

        // Write the read data to the output file
        fwrite(buffer, 1, bytes_read, output_fp);

        // Close the output file
        fclose(output_fp);
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for I/O with buffer size %d: %f seconds\n", buffer_size, cpu_time_used);

    // Close the input file
    fclose(input_fp);

    return 0;
}

