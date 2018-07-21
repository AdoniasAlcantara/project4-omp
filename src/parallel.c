#include <cet107.h>

double max(double *vec, int size) {
    double maxValue;
    int i;

    #pragma omp parallel for reduction(max:maxValue)
    for (i = 0; i < size; i++)
        if (vec[i] > maxValue)
            maxValue = vec[i];

    return maxValue;
}

double min(double *vec, int size) {
    double minValue;
    int i;

    #pragma omp parallel for reduction(min:minValue)
    for (i = 0; i < size; i++)
        if (vec[i] < minValue)
            minValue = vec[i];

    return minValue;
}

double sum(double *vec, int size) {
    double sum;
    int i;

    #pragma omp parallel for reduction(+:sum)
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
    int privMaxIdx = 0;
    int i;

    #pragma omp parallel firstprivate(privMaxIdx)
    {
        #pragma omp for nowait
        for (i = 1; i < size; i++)
            if (mat[i] > mat[privMaxIdx])
                privMaxIdx = i;

        #pragma omp critical
        if (mat[privMaxIdx] > mat[maxIdx])
            maxIdx = privMaxIdx;
    }

    return maxIdx;
}

void maxMatrixRowIdx(double *mat, int *maxIdx, int rows, int columns) {
    int i, j;

    #pragma omp parallel for
    for (i = 0; i < rows; i++) {
        maxIdx[i] = i * columns;

        #pragma omp parallel for
        for (j = 1; j < columns; j++)
            if (mat[i * columns + j] > mat[maxIdx[i]])
                maxIdx[i] = i * columns + j;
    }
}

void minMatrixColIdx(double *mat, int *minIdx, int rows, int columns) {
    int i, j;
    
    #pragma omp parallel for
    for (j = 0; j < columns; j++) {
        minIdx[j] = j;

        #pragma omp parallel for
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

    #pragma omp parallel for
    for (i = 0; i < rows; i++)
        sumRow[i] = sum(&mat[i * columns], columns);
}

void avgMatrixCol(double *mat, double *avgCol, int rows, int columns) {
    double avg;
    int i, j;

    #pragma omp parallel for private(avg)
    for (j = 0; j < columns; j++) {
        avg = 0;

        #pragma omp parallel for reduction(+:avg)
        for(i = 0; i < rows; i++)
            avg += mat[i * columns + j];

        avgCol[j] = avg / rows;
    }
}