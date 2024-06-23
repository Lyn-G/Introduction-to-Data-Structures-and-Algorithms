/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA1
* Lex.c 
* Main program for assignment 1
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"List.h"

int main(int argc, char* argv[]){
   
   FILE *input, *output;

   // will take two command line arguments 
   // Lex <input file> <output file>
   if (argc != 3) {
      fprintf(stderr, "Usage Error: files must be inputted as <input file> <output file>.\n");
      exit(EXIT_FAILURE);
   }

   // check that there are two command line arguments 
   // quit with a usage to stderr if more than or less two command line arguments are given
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

   int line_count = 0; // keep the current line that we are on
   char line[300]; // character array

   // count the number of lines in the input file
   while (fgets(line, 300, input) != NULL) {
      line_count++;

   }

   rewind(input);

   // create a string array of length n and read in the lines of the file as strings, placing them into the array
   char **A = calloc(line_count, sizeof(char*));
   int d = 0;
   while(fgets(line, 300, input)) {
      A[d] = calloc (strlen(line) + 1, sizeof(char*)); 
      strcpy(A[d], line);  
      d++;
   }

   

   // begin with an empty list, then insert the indices of the array one by one into the appropriate positions 
   // use the insertion sort algorithm
   int x = 0;
   List L = newList();

   // hard code the first element
   if (length(L) == 0) {
      append(L, x);
      moveFront(L);
   }

   x = 1;
   for (; x != line_count; x++){
      /*
      strcmp(s1, s2)<0 is true if and only if s1 comes before s2
      strcmp(s1, s2)>0 is true if and only if s1 comes after s2
      strcmp(s1, s2)==0 is true if and only if s1 is identical to s2
      */
      moveFront(L);
   
      while ( index(L) != -1) {

         if (strcmp(A[x], A[get(L)]) < 0 || strcmp(A[x], A[get(L)]) == 0) {
            insertBefore(L, x);
            moveNext(L);
            break;
         } else if (strcmp(A[x], A[get(L)]) > 0) {
            moveNext(L);
            if (index(L) == -1) {
               append(L,x);
               break;
            }
         }
         
         
      }
      
   }

   // print out to output
   moveFront(L);

   int e = 0;
   for (; e != line_count; e++) {
      fprintf(output, "%s", A[get(L)]);
      moveNext(L);
   }

   // free all items
   for (int pos = 0; pos != line_count; pos++) {
      free(A[pos]);
   }
   free(A);
   freeList(&L);
   fclose(input);
   fclose(output);

   return 0;
}
