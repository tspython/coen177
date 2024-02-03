#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h> //srand

#define num 1024

#define N num
#define L num
#define M num

#define NTHREADS N

pthread_t threads[NTHREADS];
int thread_args[NTHREADS];

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

// function prototypes
void *matrix_multiply(void *arg);

int main() {
    srand(time(NULL));

    // Fill matrices A & B with random data
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
                 matrixA[i][j] = (double) rand();
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++)
            matrixB[i][j] = (double) rand();
    }


    // Create Threads
    for(int i = 0; i < NTHREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, matrix_multiply, (void *)&thread_args[i]);
    }

    // Wait for threads to terminate
    for(int i = 0; i < NTHREADS; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++)
            printf("%.2f ", matrixA[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++)
            printf("%.2f ", matrixB[i][j]);
        printf("\n");
    }

    // Display Matrix C = A * B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < L; j++)
            printf("%.2f ", matrixC[i][j]);
        printf("\n");
    }
}

void *matrix_multiply(void *arg) {
    int row = *((int*) arg); // get row arg

    for(int i = 0; i < L; i++ ) {
        double tmp = 0;
        for(int j = 0; j < M; j++ )
            tmp += matrixA[row][j] * matrixB[j][i];
        matrixC[row][i] = tmp;
    }

    pthread_exit(NULL); // exit thread
}
