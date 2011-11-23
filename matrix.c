
#include "matrix.h"


int main(int argc, char **argv) {

    int **matrix1;
    int **matrix2;
    int **result;
    int i;
    pthread_t *threads;
    struct thread_args args[THREADS];
    struct timeval begin, end;
    long seconds, useconds;

    threads = malloc(sizeof(pthread_t) * THREADS);
    result  = malloc(sizeof(int*) * MATRIX_SIZE);
    matrix1 = malloc(sizeof(int*) * MATRIX_SIZE);
    matrix2 = malloc(sizeof(int*) * MATRIX_SIZE);

    for (i = 0; i < MATRIX_SIZE; i++) {
        result[i]  = malloc(sizeof(int) * MATRIX_SIZE);
        matrix1[i] = malloc(sizeof(int) * MATRIX_SIZE);
        matrix2[i] = malloc(sizeof(int) * MATRIX_SIZE);
    }

    createMatrix(matrix1);
    createMatrix(matrix2);

    for (i = 0; i < THREADS; i++) {
        args[i].matrix1 = matrix1;
        args[i].matrix2 = matrix2;
        args[i].result = result;
        args[i].start = i * (MATRIX_SIZE / THREADS);
        if (i == THREADS -1 ) {
            args[i].end = MATRIX_SIZE;
        } else {
            args[i].end = args[i].start + (MATRIX_SIZE / THREADS);
        }

    }

    #ifdef DEBUG
    printf("Matrix 1\n");
    out(matrix1);

    printf("\nMatrix 2\n");
    out(matrix2);
    #endif

    if (gettimeofday(&begin,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    for (i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, mult, (void *) &args[i]);
    }

    for (i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    if (gettimeofday(&end,(struct timezone *)0)) {
        fprintf(stderr, "can't get time\n");
        exit(1);
    }

    #ifdef DEBUG
    printf("\nErgebnis\n");
    out(result);
    #endif

    seconds = end.tv_sec - begin.tv_sec;
    useconds = end.tv_usec - begin.tv_usec;

    if(useconds < 0) {
        useconds += 1000000;
        seconds--;
    }

    printf("Sortierdauer: %ld sec %ld ms\n\n", seconds, useconds);

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}

void *mult(void *threadArgs) {
    struct thread_args *args = (struct thread_args*) threadArgs;
    int **a = args->matrix1;
    int **b = args->matrix2;
    int **result = args->result;
    int i, j, k;
    for (i = args->start; i < args->end; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            for (k = 0; k < MATRIX_SIZE; k++) {
                if (k == 0) {
                    result[i][j] = a[i][k] * b[k][j];
                } else {
                    result[i][j] = result[i][j] + a[i][k] * b[k][j];
                }
            }
        }
    }
    return NULL;
}

void createMatrix(int **matrix) {
    int i, j;
    srand((unsigned int) time(NULL));
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void out(int **matrix) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%10d ", matrix[i][j]);
        }
        printf("\n");
    }
}
