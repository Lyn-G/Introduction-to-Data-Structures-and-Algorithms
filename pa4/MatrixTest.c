/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA4
* MatrixTest.c 
* Test file for Matrix ADT functions
*********************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   
    Matrix m = newMatrix(4);
    puts("create graph");
    changeEntry(m, 1,3, 7.0);
    changeEntry(m, 1, 1, 2.0);
    changeEntry(m, 1,2, 1.0);
    changeEntry(m, 4, 1, 13.5);
    printMatrix(stdout, m);

    puts("\ndelete some stuff");
    changeEntry(m, 1, 3, 0);
    printMatrix(stdout, m);

    printf("The size of the matrix is: %d\n", size(m));
    printf("The number of non-zero elements in M is: %d\n", NNZ(m));

    Matrix copying = copy(m);
    puts("\nprint out copy");
    // changeEntry(copying, 2, 3, 5.4);
    printMatrix(stdout, copying);

    puts("\ndoes the original and the copy equal each other?");
    // condition ? result_if_true : result_if_false
    equals(m, copying) == 1 ? puts("it's equal!") : puts("NOT equal!");

    Matrix scale = scalarMult(2, m);
    puts("\nprinting out original matrix scaled by 2");
    printMatrix(stdout, scale);

    Matrix t = transpose(scale);
    puts("\nprinting out the transpose of the scaled matrix");
    printMatrix(stdout, t);

    changeEntry(copying, 3, 2, 6.5);
    changeEntry(t, 1, 2, 3.9);
    
    // printMatrix(stdout, copying);
    // puts("");

    puts("\ntesting out sum function");
    Matrix add = sum(copying, scale);
    printMatrix(stdout, add);

    Matrix subbb = diff(t, copying);
    puts("\ntesting out diff function");
    printMatrix(stdout, subbb);

    Matrix mult = product(t, copying);
    puts("\ntesting out product function");
    printMatrix(stdout, mult);

    puts("\nmakeZero()\n");
    makeZero(mult);
    printMatrix(stdout, mult);

    freeMatrix(&t);
    freeMatrix(&scale);
    freeMatrix(&copying);
    freeMatrix(&m);
    freeMatrix(&add);
    freeMatrix(&subbb);
    freeMatrix(&mult);

   return 0;
}
