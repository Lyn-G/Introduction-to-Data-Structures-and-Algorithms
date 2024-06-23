/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA2
* Graph.c  
* File contains all Graph ADT functions
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"
#include "Graph.h"

/*
• An array of Lists whose i
th element contains the neighbors of vertex i.
• An array of ints (or chars, or strings) whose i
th element is the color (white, gray, black) of vertex i.
• An array of ints whose i
th element is the parent of vertex i.
• An array of ints whose i
th element is the distance from the (most recent) source to vertex i.
*/
typedef struct GraphObj {
    List* neighbors;
    int *color;
    int *parent_vertex;
    int *distance;

    int vertices; // called order of the graph
    int edges; // called the size of the graph
    int source;

    // include fields storing the number of vertices, number of edges, 
    // label of the vertex that was most recently used as a source for BFS
    // all arrays be length n +1 (n is number of vertuces in the graoh)
} GraphObj;

// Use your List ADT to implement both this FIFO queue, and the adjacency lists representing the graph itself.

/*** Constructors-Destructors ***/

// having n vertices and no edges
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    assert( G!=NULL );

    G->neighbors = (List*) calloc(n + 1, sizeof(List));
    G->color = (int*) calloc(n + 1, sizeof(int));
    G->parent_vertex = (int*) calloc(n + 1, sizeof(int));
    G->distance = (int*) calloc(n + 1, sizeof(int));
    for (int i = 0; i < n+1; i++) {
        G->neighbors[i] = newList();
        G->parent_vertex[i] = NIL;
        G->distance[i] = INF;
    }
    
    G->vertices = n;
    G->edges = 0;
    G->source = -3;

    return(G);
}

// free heap memory
void freeGraph(Graph* pG) {
   
    if (pG && (*pG)) {
        for (int i = 0; i < (*pG)->vertices + 1; i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent_vertex);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

// return vertices
int getOrder(Graph G) {
    return(G->vertices);
}

// return edges
int getSize(Graph G) {
    return(G->edges);
}

// return the source vertex most recently used in function BFS() or NIL if BFS() has not yet been called
int getSource(Graph G) {
    if (G->source == -3) {
        return(NIL);
    } else {
        return(G->source);
    }
}

// return parent of vertex u in the BFS tree or NIL
// pre-condition: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if (1 > u && u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling getParent() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    if (G->parent_vertex[u] == NIL) {
        return (NIL);
    } else {
        return (G->parent_vertex[u]);
    }
}

// return the distance from source to vertex u or INF if BFS() hasn't been called
// pre-condition: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if (1 > u && u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling getDist() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    if (G->distance[u] == INF) {
        return (INF);
    } else {
        return (G->distance[u]);
    }
}

// appends List the vertices of a shortest path in G from source to u
// or append to L the value of NIL
// pre-condition: getsource(G) != NIL
// pre-condition: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) {
        fprintf( stderr, "Graph Error: calling getPath() on graph that has not had BFS() called yet. \n");
        exit(EXIT_FAILURE);
    }

    if (1 > u && u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling getPath() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    // x = destination = u
    // s is source, and source has already been put in
    if (u == getSource(G)) {
        append(L, getSource(G));
    } else if (G->parent_vertex[u] == NIL) {
        append(L, NIL);
    } else  {
        getPath(L, G, G->parent_vertex[u]);
        append(L, u);
    }
}

/*** Manipulation procedures ***/
// deletes all edges of G
void makeNull(Graph G) {
    for (int i = 0; i < G->vertices; i++) {
        clear(G->neighbors[i]);
    }
}

// inserts a new edge joiing u to v
// u is added to the List of v
// v to the adjacency List of u
// pre-condition: both integers must be in range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
    if (1 > u && u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addEdge() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    if (1 > v && v > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addEdge() with an invalid argument v.\n");
        exit(EXIT_FAILURE);
    }

    addArc(G, u, v);
    addArc(G, v, u);
    G->edges--;
}

// inserts a new directed edge from u to v
// i.e. v is added to the List of u (but not u to the List of v)
// pre-condition: both integers must be in range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
        if (1 > u && u > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addArc() with an invalid argument u.\n");
        exit(EXIT_FAILURE);
    }

    if (1 > v && v > getOrder(G)) {
        fprintf( stderr, "Graph Error: calling addArc() with an invalid argument v.\n");
        exit(EXIT_FAILURE);
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

// runs BFS on the Graph with source s, setting the color, distance, parent, and source fields of G
// white = 1
// gray = 2
// black = 3
void BFS(Graph G, int s) {
    G->source = s;

    for (int x = 0; x < G->vertices + 1; x++) {
        G->color[x] = 1; // white
        G->distance[x] = INF;
        G->parent_vertex[x] = NIL;
    }

    G->color[s] = 2;
    G->distance[s] = 0;
    G->parent_vertex[s] = NIL;

    List Q = newList();
    append(Q, s);

    int i;
    while (length(Q) != 0) {
        moveFront(Q);
        i = front(Q);
        moveNext(Q);
        deleteFront(Q);

        moveFront(G->neighbors[i]);
        int y = 0;
        while (index(G->neighbors[i]) != -1) {
            y = get(G->neighbors[i]);
            if (G->color[y] == 1) { // white
                G->color[y] = 2; // gray
                G->distance[y] = G->distance[i] + 1;
                G->parent_vertex[y] = i;
                append(Q, y);
            }
            moveNext(G->neighbors[i]);
        }

        G->color[i] = 3; // black
        
    }

    freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
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