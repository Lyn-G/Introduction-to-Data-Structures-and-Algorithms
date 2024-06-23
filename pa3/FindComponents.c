/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA3
* FindComponents.c
* File contains the main function for PA3
*********************************************************************************/ 

#include "Graph.h"
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

    int vertices_number = 0; // number of vertices in the graph
    int first = -3;
    int second = -3;
    fscanf(input, "%d", &vertices_number);
    Graph G = newGraph(vertices_number);

    while( first != 0 && second != 0) {
        fscanf(input, "%d %d", &first, &second);

        if (first == 0 && second == 0) {
            break;
        }

        addArc(G, first, second);
    }
    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);
    fprintf(output, "\n");

    List L = newList();
    for(int i=1; i<=vertices_number; i++) append(L, i);

    DFS(G, L);

    Graph T = transpose(G);
    DFS(T, L);

    int number = 0;
    for (int x = 1; x < getOrder(T) + 1; x++) {
        if (getParent(T, x) == -2) {
            number++;
        }
    }

    int counter = 1;
    fprintf(output, "G contains %d strongly connected components:\n", number);

    List U = newList();

    for(moveBack(L); index(L) != -1; movePrev(L)) {
        if (getParent(T, get(L)) == -2) {
            prepend(U, get(L));
            fprintf(output, "Component %d: ", counter);
            printList(output, U);
            clear(U);
            counter++;
        } else {
            prepend(U, get(L));
        }
        
    }

    fclose(input);
    fclose(output);
    
    freeGraph(&G);
    freeGraph(&T);
    freeList(&L);

    return 0;
}