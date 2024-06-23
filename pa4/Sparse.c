/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA4
* Sparse.c
* Main program file
*********************************************************************************/
#include "Matrix.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {

    FILE *input, *output;

   // will take two command line arguments 
   // Lex <input file> <output file>
   if (argc != 3) {
      fprintf(stderr, "Usage Error: files must be inputted as <input file> <output file>.\n");
      exit(EXIT_FAILURE);
   }

   input = fopen(argv[1], "r");

   if (input == NULL) {
      fprintf(stderr, "File Error: Unable to open input file for reading. \n");
      exit(EXIT_FAILURE);
   }

   output = fopen(argv[2], "w");

   if (output == NULL) {
      fprintf(stderr, "File Error: Unable to open output file for writing. \n");
      exit(EXIT_FAILURE);
   }

    int n = 0; // number of vertices in the graph
    int a = -3;
    int b = -3;

    fscanf(input, "%d %d %d", &n, &a, &b);

    Matrix A = newMatrix(n );
    Matrix B = newMatrix(n );

    fscanf(input, " ");

    // scan matrix A's numbers
    int row = 0; int column = 0; double value = 0.0;
    for (int i = 0; i < a; i++) {
        fscanf(input, "%d %d %le", &row, &column, &value);
        changeEntry(A,row, column, value);
    }
    fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output, A);

    fscanf(input, " ");

    // scan matrix B's numbers
    for (int k = 0; k < b; k++) {
        fscanf(input, "%d %d %le", &row, &column, &value);
        changeEntry(B,row, column, value);
    }

    fprintf(output, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(output, B);

    // scaling A by 1.5
    Matrix T = scalarMult(1.5, A);
    fprintf(output, "\n(1.5)*A =\n");
    printMatrix(output, T);
    freeMatrix(&T);

    // adding matricies
    fprintf(output, "\nA+B =\n");
    Matrix add = sum(A, B);
    printMatrix(output, add);
    freeMatrix(&add);

    // adding A with A
    fprintf(output, "\nA+A =\n");
    Matrix plus = sum(A, A);
    printMatrix(output, plus);
    freeMatrix(&plus);

    // B - A
    fprintf(output, "\nB-A =\n");
    Matrix subtract = diff(B, A);
    printMatrix(output, subtract);
    freeMatrix(&subtract);

    // A - A
    fprintf(output, "\nA-A =\n");
    Matrix minus_A = diff(A,A);
    printMatrix(output, minus_A);
    freeMatrix(&minus_A);

    // transpose of A
    fprintf(output, "\nTranspose(A) =\n");
    Matrix gA = transpose(A);
    printMatrix(output, gA);
    freeMatrix(&gA);

    // A mult. B
    fprintf(output, "\nA*B =\n");
    Matrix AxB = product(A, B);
    printMatrix(output, AxB);
    freeMatrix(&AxB);
    
    // B mult. B
    fprintf(output, "\nB*B =\n");
    Matrix BxB = product(B, B);
    printMatrix(output, BxB);
    freeMatrix(&BxB);

    // close and free all memory
    fclose(input);
    fclose(output);

    freeMatrix(&A);
    freeMatrix(&B);

    return 0;
}