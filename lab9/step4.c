#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp, *fp_out;
    char *buffer;
    int bufferSize;
    char outputFileName[256];

    bufferSize = atoi(argv[2]);

    buffer = (char *)malloc(bufferSize);
    
    fp = fopen(argv[1], "rb");
    

    snprintf(outputFileName, sizeof(outputFileName), "%s_copy", argv[1]);
    fp_out = fopen(outputFileName, "wb");
    

    while (fread(buffer, 1, bufferSize, fp) > 0) {
        fwrite(buffer, 1, bufferSize, fp_out);
    }

    fclose(fp);
    fclose(fp_out);
    free(buffer);
    return 0;
}
