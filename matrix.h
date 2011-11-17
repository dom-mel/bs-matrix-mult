#ifndef GENNUM_H
#define GENNUM_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MATRIX_SIZE 2

int main(int argc, char **argv);
void createMatrix(int **matrix);
void mult(int **a, int **b, int **result);
void out(int **matrix);

#endif
