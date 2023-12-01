#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100

int **matrixA, **matrixB, **resultMatrix;
int rowsA, colsA, rowsB, colsB;

typedef struct {
    int row;
    int col;
} MatrixIndex;

void *add(void *arg) {
    MatrixIndex *index = (MatrixIndex *)arg;
    resultMatrix[index->row][index->col] = matrixA[index->row][index->col] + matrixB[index->row][index->col];
    free(arg);
    pthread_exit(NULL);
}

void *subtract(void *arg) {
    MatrixIndex *index = (MatrixIndex *)arg;
    resultMatrix[index->row][index->col] = matrixA[index->row][index->col] - matrixB[index->row][index->col];
    free(arg);
    pthread_exit(NULL);
}

void *multiply(void *arg) {
    MatrixIndex *index = (MatrixIndex *)arg;
    int sum = 0;
    for (int i = 0; i < colsA; ++i)
        sum += matrixA[index->row][i] * matrixB[i][index->col];
    resultMatrix[index->row][index->col] = sum;
    free(arg);
    pthread_exit(NULL);
}

int **allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
        matrix[i] = (int *)malloc(cols * sizeof(int));
    return matrix;
}

void getMatrixValues(int **matrix, int rows, int cols) {
    printf("Enter matrix values:\n");
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            scanf("%d", &matrix[i][j]);
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; ++i)
        free(matrix[i]);
    free(matrix);
}

int main() {
    printf("Enter dimensions for matrix A (rows columns): ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Enter dimensions for matrix B (rows columns): ");
    scanf("%d %d", &rowsB, &colsB);

    if (colsA != rowsB) {
        printf("Error: Matrix multiplication not possible with the given dimensions.\n");
        return 1;
    }

    matrixA = allocateMatrix(rowsA, colsA);
    matrixB = allocateMatrix(rowsB, colsB);
    resultMatrix = allocateMatrix(rowsA, colsB);

    getMatrixValues(matrixA, rowsA, colsA);
    getMatrixValues(matrixB, rowsB, colsB);

    printf("\nMatrix A:\n");
    printMatrix(matrixA, rowsA, colsA);

    printf("\nMatrix B:\n");
    printMatrix(matrixB, rowsB, colsB);

    pthread_t threads[MAX_SIZE];
    MatrixIndex *index;

    // Addition
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j) {
            index = malloc(sizeof(MatrixIndex));
            index->row = i;
            index->col = j;
            pthread_create(&threads[i * colsA + j], NULL, add, index);
        }

    for (int i = 0; i < rowsA * colsA; ++i)
        pthread_join(threads[i], NULL);

    printf("\nMatrix Addition Result:\n");
    printMatrix(resultMatrix, rowsA, colsA);

    // Subtraction
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j) {
            index = malloc(sizeof(MatrixIndex));
            index->row = i;
            index->col = j;
            pthread_create(&threads[i * colsA + j], NULL, subtract, index);
        }

    for (int i = 0; i < rowsA * colsA; ++i)
        pthread_join(threads[i], NULL);

    printf("\nMatrix Subtraction Result:\n");
    printMatrix(resultMatrix, rowsA, colsA);

    // Multiplication
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsB; ++j) {
            index = malloc(sizeof(MatrixIndex));
            index->row = i;
            index->col = j;
            pthread_create(&threads[i * colsB + j], NULL, multiply, index);
        }

    for (int i = 0; i < rowsA * colsB; ++i)
        pthread_join(threads[i], NULL);

    printf("\nMatrix Multiplication Result:\n");
    printMatrix(resultMatrix, rowsA, colsB);

    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);
    freeMatrix(resultMatrix, rowsA);

    return 0;
}

