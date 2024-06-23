/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA2
* FindPath.c  
* Main program for assignment 2
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"

/*
1. Read and store the graph and print out its adjacency list representation.
2. Enter a loop that processes the second part of the input. Each iteration of the loop should read in one
pair of vertices (source, destination), run BFS on the source vertex, print the distance to the destination
vertex, then find and print the resulting shortest path, if it exists, or print a message that no path from
source to destination exists (as in the above example).
*/

// BFS requires each vertex v in G possess:
// color[v], distance[v], parent[v]

// white vertices are those that are as yet undiscovered, black vertices are finished, and the gray
// vertices are discovered, but not all of their neighbors have been discovered
// The gray vertices thus form the frontier between undiscovered and finished vertices

// read the file format on the pdf

// perform a BFS from the given source vertex
// use the results of BFS to print out the distance from the source vertex to the destination vertex

int main(int argc, char* argv[]){

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

        addEdge(G, first, second);
    }
    printGraph(output, G);
    fprintf(output, "\n");
    List L = newList();

    first = -3;
    second = -3;
    while (first != 0 && second != 0) {
        clear(L);
        fscanf(input, "%d %d", &first, &second);

        if (first == 0 && second == 0) {
            break;
        }

        BFS(G, first);
        getPath(L, G, second);
        moveFront(L);

        if (get(L) != -2) {
            fprintf(output, "The distance from %d to %d is %d\n", first, second, length(L) - 1);
            fprintf(output, "A shortest %d-%d path is: ", first, second);
            
            while (index(L) != -1) {
                fprintf(output, "%d ", get(L));
                moveNext(L);
            }
        } else if (get(L) == -2) {
            fprintf(output, "The distance from %d to %d is infinity\n", first, second);
            fprintf(output, "No %d-%d path exists", first, second);
        }
        fprintf(output, "\n\n");
    }
    
    freeList(&L);
    freeGraph(&G);
    fclose(input);
    fclose(output);

    return 0;
}