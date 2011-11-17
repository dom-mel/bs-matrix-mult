
#include "matrix.h"


int main(int argc, char **argv) {

    int **matrix1;
    int **matrix2;
    int **result;
    int i;

    result = malloc(sizeof(int*) * MATRIX_SIZE);
    matrix1 = malloc(sizeof(int*) * MATRIX_SIZE);
    matrix2 = malloc(sizeof(int*) * MATRIX_SIZE);
    for (i = 0; i < MATRIX_SIZE; i++) {
        result[i] = malloc(sizeof(int) * MATRIX_SIZE);
        matrix1[i] = malloc(sizeof(int) * MATRIX_SIZE);
        matrix2[i] = malloc(sizeof(int) * MATRIX_SIZE);
    }
 
    createMatrix(matrix1);
    createMatrix(matrix2);

    printf("Matrix 1\n");
    out(matrix1);

    printf("\nMatrix 2\n");
    out(matrix2);

    mult(matrix1, matrix2, result);

    printf("\nErgebnis\n");
    out(result);

    free(matrix1);
    free(matrix2);
    free(result);
    
    return 0;
}

void mult(int **a, int **b, int **result) {
    int i, j, k;
    for (i = 0; i < MATRIX_SIZE; i++) {
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
