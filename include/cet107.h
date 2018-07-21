#ifndef CET107_H
#define CET107_H

/*
 * Vector functions
 */
double max(double *vec, int size);
double min(double *vec, int size);
double sum(double *vec, int size);
double avg(double *vec, int size);

/*
 * Matrix functions
 */ 
// Project 1: Returns maximum value of the matrix
int maxMatrixIdx(double *matrix, int rows, int columns);

// Project 2: Returns index relative to the maximum value of each row in the matrix
void maxMatrixRowIdx(double *matrix, int *maxIdx, int rows, int columns);

// Project 3: Returns index relative to the minimum value of each column in the matrix
void minMatrixColIdx(double *matrix, int *minIdx, int rows, int columns);

// Project 4: Returns sum of the matrix
double sumMatrix(double *matrix, int rows, int columns);

// Projeto 5: Returns the sum of each row in the matrix
void sumMatrixRow(double *matrix, double *sumRow, int rows, int columns);

// Projeto 6: Returns the average of each row in the matrix
void avgMatrixCol(double *matrix, double *avgCol, int rows, int columns);

#endif /* CET107_H */