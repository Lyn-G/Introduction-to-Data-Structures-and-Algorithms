/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA3
* GraphTest.c
* Tests functions from Graph.c
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,3);
   addArc(G, 1,8);
   addArc(G, 2,4);
   addArc(G, 2,7);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,7);
   addArc(G, 3,5);
   addArc(G, 3,4);
   addArc(G, 6,1);
   addArc(G, 6,5);
   addArc(G, 8,4);
   addArc(G, 8,1);
   addEdge(G, 5, 6);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   puts("printing copied graph");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   puts("printing transpose");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   printf("Graph T has %d vertices and %d edges.\n", getOrder(T), getSize(G));

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}

