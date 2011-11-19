#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 2
#define THREADS 2
#define DEBUG 1

int main(int argc, char **argv);
void createMatrix(int **matrix);
void *mult(void *threadArgs);
void out(int **matrix);

struct thread_args {
    int **matrix1;
    int **matrix2;
    int **result;
    int start;
    int end;
};


#endif
