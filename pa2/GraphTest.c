/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA2
* GraphTest.c 
* Test client for Graph ADT 
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
  
   Graph g = newGraph(5);

    addArc(g, 2, 1);
    addArc(g, 1, 3);
    addArc(g, 5, 2);

    printf("Printing out graph after adding arcs:\n");
    printGraph(stdout, g);
    makeNull(g);

   for(int i=1; i<5; i++){
      if( i%5!=0 ) addEdge(g, i, i+1);
   }

    printf("Printing out graph after nulling and adding edges:\n");
    printGraph(stdout, g);

    printf("There are %d vertices and %d edges.\n", getOrder(g), getSize(g));

    List l = newList();
    clear(l);
    BFS(g, 2);
    printf("After doing BFS(), the source vertex is %d, the parent of the source vertex is %d, and the distance from the source to vertex 3 is %d.\n", getSource(g), getParent(g, 2), getDist(g, 3));

   getPath(l, g, 3);
    
    fprintf(stdout, "A shortest 2-3 path is: ");
    
    moveFront(l);
    while (index(l) != -1) {
        printf("%d ", get(l));
        moveNext(l);
    }
    puts("");
    freeList(&l);
    freeGraph(&g);

   return(0);
}