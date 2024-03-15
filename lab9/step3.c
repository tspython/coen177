#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char *buffer;
    int bufferSize;

    bufferSize = atoi(argv[2]);

    buffer = (char *)malloc(bufferSize);

    fp = fopen(argv[1], "rb");

    while (fread(buffer, 1, bufferSize, fp) > 0) {
    }

    fclose(fp);
    free(buffer);
    return 0;
}
