#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    char *inputFileName;
    char outputFileName[256];
    int bufferSize;
} ThreadData;

void *copyFile(void *threadData) {
    ThreadData *data = (ThreadData *)threadData;
    FILE *fp = fopen(data->inputFileName, "rb");
    FILE *fp_out = fopen(data->outputFileName, "wb");
    char *buffer = (char *)malloc(data->bufferSize);

    while (fread(buffer, 1, data->bufferSize, fp) > 0) {
        fwrite(buffer, 1, data->bufferSize, fp_out);
    }

    fclose(fp);
    fclose(fp_out);
    free(buffer);

    return NULL;
}

int main(int argc, char *argv[]) {
    int numThreads = atoi(argv[3]);
    pthread_t threads[numThreads];
    ThreadData data[numThreads];

    int bufferSize = atoi(argv[2]);

    int i;
    for (i = 0; i < numThreads; i++) {
        data[i].inputFileName = argv[1];
        snprintf(data[i].outputFileName, sizeof(data[i].outputFileName), "%s_copy%d", argv[1], i);
        data[i].bufferSize = bufferSize;

        pthread_create(&threads[i], NULL, copyFile, (void *)&data[i]);
    }

    for (i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
