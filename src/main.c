#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "cet107.h"

// Default dimensions of the matrix
#define ROWS 256
#define COLS 512

// Default iterations
#define ITER 1

// Usage message
void usage(char *program) {
    fprintf(stderr,
        "Usage: %s [-h] [-i iterations] "
        "[-o output_file] [rows [columns]]\n", program);
}

int main(int argc, char **argv) {
    // Output
    FILE *out = stdout;
    
    // Matrix variables
    double *matrix; // Matrix as 1-dimensional array
    double result;

    // Matrix dimensions
    int rows = ROWS;
    int columns = COLS;

    // Time measurement
    double elapsedTime;
    double avgTime = 0;

    // Loop variables
    int iterations = ITER;
    int i, j;

    // CLI options
    int option;

    /*
    * Parsing CLI options
    */
    while ((option = getopt(argc, argv, "hi:o:s")) != -1) {
        switch (option) {
            // Assigns the number of iterations
            case 'i':
                if ((iterations = atoi(optarg)) < 1)
                    iterations = 1;
                break;
            
            // Redirects standard output to file
            case 'o':
                if ((out = fopen(optarg, "a+")) == NULL) {
                    fprintf(stderr, "%s: I/O error.\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;

            // Shows usage message
            case 'h':
                usage(argv[0]);
                exit(EXIT_SUCCESS);
            
            // Caught a CLI syntax error
            case '?':
                exit(EXIT_FAILURE);
        }
    }

    // Parsing matrix rows and columns arguments
    if (optind < argc) {
        rows = atoi(argv[optind]);

        if (++optind < argc)
            columns = atoi(argv[optind]);
    }
    /*
    * End parse
    */

    fprintf(out,
        "Rows:\t\t%d\n"
        "Columns:\t%d\n"
        "Iterations:\t%d\n\n",
        rows, columns, iterations);
    fputs("Initializing array...\n", out);
    fflush(out);

    // Matrix initialization
    elapsedTime = omp_get_wtime();
    matrix = (double *) malloc(rows * columns * sizeof(double));

    if (matrix == NULL) {
        fputs("\nBad memory allocation.\n", stderr);
        exit(EXIT_FAILURE);
    }

    srandom(0);

    // Fill matrix with random values between -1 and 1
    for (i = 0; i < rows; i++)
        for (j = 0; j < columns; j++)
            matrix[i * columns + j] = ((double) random() / RAND_MAX) * 2.0 - 1.0;

    elapsedTime = omp_get_wtime() - elapsedTime;
    fprintf(out, "Ok (%.2f sec).\n\n", elapsedTime);
    fputs(
        "--------------------------------------------\n"
        "Iteration\tResult\t\tElapsed time\n"
        "--------------------------------------------\n", out
    );

    // This loop performs array operations repeatedly as many times as desired
    for (i = 0; i < iterations; i++) {
        elapsedTime = omp_get_wtime();
        result = sumMatrix(matrix, rows, columns); // Calculates array sum
        avgTime += elapsedTime = omp_get_wtime() - elapsedTime;
        fprintf(out, "%d\t\t%f\t%f\n", i + 1, result, elapsedTime);
        fflush(out);
    }

    avgTime /= iterations;
    fputs("--------------------------------------------\n", out);
    fprintf(out, "\nAverage time: %f sec.\n", avgTime);

    fclose(out);
    free(matrix);
    return EXIT_SUCCESS;
}