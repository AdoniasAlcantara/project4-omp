#include <cet107.h>

double max(double *vec, int size) {
    double maxValue = vec[0];
    int i;

    for (i = 1; i < size; i++)
        if (vec[i] > maxValue)
            maxValue = vec[i];

    return maxValue;
}

double min(double *vec, int size) {
    double minValue = vec[0];
    int i;

    for (i = 1; i < size; i++)
        if (vec[i] < minValue)
            minValue = vec[i];

    return minValue;
}

double sum(double *vec, int size) {
    double sum = 0;
    int i;

    for (i = 0; i < size; i++)
        sum += vec[i];

    return sum;
}

double avg(double *vec, int size) {
    return sum(vec, size) / size;
}

int maxMatrixIdx(double *mat, int rows, int columns) {
    int size = rows * columns;
    int maxIdx = 0;
    int i;

    for (i = 1; i < size; i++)
        if (mat[i] > mat[maxIdx])
            maxIdx = i;

    return maxIdx;
}

void maxMatrixRowIdx(double *mat, int *maxIdx, int rows, int columns) {
    int i, j;

    for (i = 0; i < rows; i++) {
        maxIdx[i] = i * columns;

        for (j = 1; j < columns; j++)
            if (mat[i * columns + j] > mat[maxIdx[i]])
                maxIdx[i] = i * columns + j;
    }
}

void minMatrixColIdx(double *mat, int *minIdx, int rows, int columns) {
    int i, j;

    for (j = 0; j < columns; j++) {
        minIdx[j] = j;

        for (i = 1; i < rows; i++)
            if (mat[i * columns + j] < mat[minIdx[j]])
                minIdx[j] = i * columns + j;
    }
}

double sumMatrix(double *mat, int rows, int columns) {
    return sum(mat, rows * columns);
}

void sumMatrixRow(double *mat, double *sumRow, int rows, int columns) {
    int i;
    
    for (i = 0; i < rows; i++)
        sumRow[i] = sum(&mat[i * columns], columns);
}

void avgMatrixCol(double *mat, double *avgCol, int rows, int columns) {
    int i, j;
    
    for (j = 0; j < columns; j++) {
        avgCol[j] = 0;

        for (i = 0; i < rows; i++)
            avgCol[j] += mat[i * columns + j];

        avgCol[j] /= rows;
    }
}