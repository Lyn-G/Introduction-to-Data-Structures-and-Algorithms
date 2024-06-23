/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA3
* Graph.c  
* File contains all Graph ADT functions
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"
#include "Graph.h"

typedef struct GraphObj {
    List* neighbors;
    char *color;
    int *parent;
    int *distance;
    int *discover_time;
    int *finish_times;
    int vertices;
    int edges;

} GraphObj;

// Constructors-Destructors

// Function newGraph() will return a reference to a new graph object containing n vertices and no edges
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    assert( G!=NULL );

    G->neighbors = (List*) calloc(n + 1, sizeof(List));
    G->color = (char*) calloc(n + 1, sizeof(char));
    G->parent = (int*) calloc(n + 1, sizeof(int));
    G->distance = (int*) calloc(n + 1, sizeof(int));
    G->discover_time = (int*) calloc(n + 1, sizeof(int));
    G->finish_times = (int*) calloc(n + 1, sizeof(int));

    for (int i = 0; i < n+1; i++) {
        G->neighbors[i] = newList();
        G->color[i] = 'w';
        G->parent[i] = NIL;
        G->distance[i] = -3;
        G->discover_time[i] = UNDEF;
        G->finish_times[i] = UNDEF;
    }

    G->vertices = n;
    G->edges = 0;

    return G;
}

void freeGraph(Graph* pG) {

    if (pG && (*pG)) {
        for (int i = 0; i < (*pG)->vertices + 1; i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free((*pG)->discover_time);
        free((*pG)->finish_times);
        free(*pG);
        *pG = NULL;
    }
}
// Access functions

// getOrder() returns the number of vertices 
int getOrder(Graph G) {
    return G->vertices;
}
// edges
int getSize(Graph G) {
    return G->edges;
}

int getParent(Graph G, int u) { /* Pre: 1<=u<=n=getOrder(G) */
    if ((1 > u) || (1 > getOrder(G))) {
        fprintf( stderr, "Graph Error: calling getParent() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    return G->parent[u];
}

int getDiscover(Graph G, int u) { /* Pre: 1<=u<=n=getOrder(G) */
    if ((1 > u) || (1 > getOrder(G))) {
        fprintf( stderr, "Graph Error: calling getDiscover() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    return G->discover_time[u];
}

int getFinish(Graph G, int u){  /* Pre: 1<=u<=n=getOrder(G) */
    if ((1 > u) || (1 > getOrder(G))) {
        fprintf( stderr, "Graph Error: calling getFinish() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    return G->finish_times[u];
}

// Manipulation procedures
void addArc(Graph G, int u, int v) { /* Pre: 1<=u<=n, 1<=v<=n */
    if (1 > u || u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addArc() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    if (1 > v || v > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addArc() with an invalid argument v.\n");
        exit(EXIT_FAILURE);
    }

    if (length(G->neighbors[u]) != 0) {
            
        moveBack(G->neighbors[u]);

        for (; index(G->neighbors[u]) != -1; movePrev(G->neighbors[u])) {
            if (v == get(G->neighbors[u])) {
                return;
            }
        }
    }

    moveBack(G->neighbors[u]);
    if (length(G->neighbors[u]) == 0) {
        append(G->neighbors[u],v);
    }


    while (index(G->neighbors[u]) != -1) {
        int sorting = get(G->neighbors[u]);

        if (sorting <= v) {
            insertAfter(G->neighbors[u], v);
            movePrev(G->neighbors[u]);
            break;
        } else if (sorting > v) {
            movePrev(G->neighbors[u]);
            if (index(G->neighbors[u]) == -1) {
               prepend(G->neighbors[u],v);
               break;
            }
        } 
    }
    G->edges++;
}

void addEdge(Graph G, int u, int v) { /* Pre: 1<=u<=n, 1<=v<=n */
    if (1 > u || u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addEdge() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    if (1 > v || v > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addEdge() with an invalid argument v.\n");
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->edges--;
}

void Visit(Graph G, int *time, int x) {
    G->discover_time[x] = ++(*time);
    G->color[x] = 'g';

    moveFront(G->neighbors[x]);
    while (index(G->neighbors[x]) != -1) {
        
        if (G->color[get(G->neighbors[x])] == 'w') {
            G->parent[get(G->neighbors[x])] = x;
            Visit(G, time, get(G->neighbors[x]));
        }
        moveNext(G->neighbors[x]);
    }

    G->color[x] = 'b';
    G->finish_times[x] = ++(*time);

}

// Pre: length(S)==getOrder(G)
/*
Recall DFS() calls the recursive algorithm Visit() (referred to as DFS-Visit() in the text), and uses a variable
called time that is static over all recursive calls to Visit(). Observe that this function is not mentioned in
the above catalog (Graph.h) and therefore is to be considered a private helper function in Graph.c.
*/

// do the white and other stuff first
void DFS(Graph G, List S) {
    if (length(S) != getOrder(G)) {
        fprintf( stderr, "Graph Error: calling DFS() while List and Graph are not the same length.\n");
        exit(EXIT_FAILURE);
    }

    int time = 0;

    for (int x = 1; x < G->vertices + 1; x++) {
        G->color[x] = 'w';
        G->parent[x] = NIL;
    }

    moveFront(S);
    while(index(S) != -1) {
        if (G->color[get(S)] == 'w') {
            Visit(G, &time, get(S));
        }
        moveNext(S);
    }
    clear(S);
    for (int i = 1; i < G->vertices + 1; i++) {
        moveFront(S);

        if (length(S) == 0) {
            append(S,i);
        }

        while (index(S) != -1) {
            int sorting = G->finish_times[get(S)];

            if (sorting <= G->finish_times[i]) {
                insertBefore(S, i);
                moveNext(S);
                break;
            } else if (sorting > G->finish_times[i]) {
                moveNext(S);
                if (index(S) == -1) {
                    append(S,i);
                    break;
                }
            } 
        }
    }
}

// Other Functions
Graph transpose(Graph G) {
    Graph new = newGraph(getOrder(G));

    for (int i = 1; i < G->vertices + 1; i++) {
        moveFront(G->neighbors[i]);

        for (int k = 1; index(G->neighbors[i]) != -1; k++) {
            addArc(new, get(G->neighbors[i]), i);
            moveNext(G->neighbors[i]);
        }
    }
    return new;
}

// copyGraph() returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G) {
    Graph new = newGraph(getOrder(G));

    for (int i = 1; i < G->vertices + 1; i++) {
        moveFront(G->neighbors[i]);

        for (int k = 1; index(G->neighbors[i]) != -1; k++) {
            addArc(new, i, get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
    }
    return new;
}

void printGraph(FILE* out , Graph G) {
    for (int i = 1; i < G->vertices + 1; i++) {
        fprintf(out, "%d: ", i);
        moveFront(G->neighbors[i]);

        for (int k = 1; index(G->neighbors[i]) != -1; k++) {
            fprintf(out, "%d ", get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }

        fprintf(out, "\n");
    }
}