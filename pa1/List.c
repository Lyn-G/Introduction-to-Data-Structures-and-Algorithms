/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA1
* List.c 
* File contains all List ADT functions
*********************************************************************************/ 

#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
    int data;
    Node next;
    Node prev;
} NodeObj;


typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;

    // length of a List, and the index of the cursor element
    int length;
    int index;
} ListObj;

// Node ADT

// newNode()
// Returns reference to new Node object.
Node newNode(int data){ 
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// List

// Creates and returns a new empty List.
List newList(void) {
    List l;
    l = malloc(sizeof(ListObj));
    assert (l != NULL);
    
    l->front = NULL;
    l->back = NULL;
    l->cursor = NULL;
    l->length = 0;
    l->index = -1;
    return(l);
}

void freeList(List* l) {
   	if (l) {
        Node N = NULL;

        while ((*l)->front != NULL) {
            N = (*l)->front->next;
            freeNode(&(*l)->front);
            (*l)->front = N;
        }
    }
    free(*l);
    *l = NULL;
}

int length(List L) { // Returns the number of elements in L.
    return L->length;
}

int index(List L) { // Returns index of cursor element if defined, -1 otherwise.
    if (L->cursor == NULL) {
        return -1;
    } else {
        return L->index;
    }
}

int front(List L) { // Returns front element of L. Pre: length()>0
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling front() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

int back(List L) { // Returns back element of L. Pre: length()>0
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling back() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

int get(List L) { // Returns cursor element of L. Pre: length()>0, index()>=0
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling get() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling get() on cursor that is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Returns true if and only if Lists A and B are in same
// state, and returns false otherwise.
// Manipulation procedures 
bool equals(List A, List B) { 
    if( A==NULL || B==NULL ){
        fprintf(stderr, "List Error: calling equals() on list(s) that are NULL.\n");
        exit(EXIT_FAILURE);
   }

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Resets L to its original empty state.
// clear the nodes, then clear the list
void clear(List l) {
    if (l) {
        Node N = NULL;

        while ((l)->front != NULL) {
            N = (l)->front->next;
            freeNode(&(l)->front);
            (l)->front = N;
        }
    }

    l->front = l->back = l->cursor = NULL;
    l->length = 0;
    l->index = -1;
}

// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void set(List L, int x){
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling set() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling set() on cursor that is NULL.\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
} 

// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L) {
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L) {
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L) {
    // printf("cursor: %d \nindex: %d\nlength: %d\n", L->cursor->data, L->index, L->length);
    if (L->cursor == NULL) {
        return;
    }
    
    // If cursor is defined and not at front, move cursor one step toward the front of L
    if (L->cursor != NULL) {
        if (L->index >= 0) {
            L->cursor = L->cursor->prev;
            L->index--;
        }
        
        // if cursor is defined and at front, cursor becomes undefined;
        if (L->index == -1) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}

void moveNext(List L) {
    // printf("cursor: %d \nindex: %d\nlength: %d\n", L->cursor->data, L->index, L->length);
    // if cursor is undefined, do nothing
   if (L->cursor == NULL) {
        return;
    }

    // If cursor is defined and not at back, move cursor one step toward the back of L; 
    if (L->cursor != NULL && L->cursor->next != NULL) {
            L->cursor = L->cursor->next;
            L->index++;
        
    }

    // if cursor is defined and at back, cursor becomes undefined; 
    else if (L->index == (L->length - 1)) {
            L->cursor = NULL;
            L->index = -1;
        }
}

// Insert new element into L. 
void prepend(List L, int x) {

    Node N = newNode(x);

    if(L->length == 0) {
        L->front = N;
        L->back = N;
    } else {
        // If L is non-empty, insertion takes place before front element.
        L->front->prev = N;
        // L->front = N;
        N->next = L->front;
        L->front = N;
    }
    L->length++;
    if (L->cursor != NULL) {
            L->index++;
        }
}

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int x) {
    Node N = newNode(x);

    if(L->length == 0) {
        L->front = N;
        L->back = N;
        L->length++;
    } else {
        L->back->next = N;
        // L->back = N;
        N->prev = L->back;
        L->back = N;
        L->length++;
    }
} 

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling insertBefore() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling insertBefore() on cursor that is NULL.\n");
        exit(EXIT_FAILURE);
    }

    // if the node behind cursor is NULL
    if (L->cursor->prev == NULL) {
        prepend(L, x);
    } else  {
        Node M = newNode(x);

        M->prev = L->cursor->prev;
        M->next = L->cursor;
        L->cursor->prev->next = M;
        L->cursor->prev = M;
        L->length++;
        L->index++;
    }
}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling insertAfter() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling insertAfter() on cursor that is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor->next == NULL) {
        Node N = newNode(x);

        if(L->length == 0) {
            L->front = N;
            L->back = N;
        } else {
            L->back->next = N;
            N->prev = L->back;
            L->back = N;
        }
        L->length++;
    } else {
        Node M = newNode(x);

        M->next = L->cursor->next;
        M->prev = L->cursor;
        L->cursor->next->prev = M;
        L->cursor->next = M;
        L->length++;
    }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling deleteFront() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }

    if (L->length == 1) {
        Node M = L->front;
        freeNode(&M);
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
    } else {

        // make cursor undefined if cursor is at the front
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        }

        Node N = L->front;

        L->front = L->front->next;
        L->front->prev = NULL;
        freeNode(&N);
        L->length--;

        // decrease index if cursor isn't NULL
        if (L->cursor != NULL) {
            L->index--;
        }
    }
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling deleteBack() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }

    // edge cases
    if (L->length == 1) {
        Node M = L->back;

        freeNode(&M);
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
    } else {
        
        // make cursor undefined if it is at back
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        }
        Node N = L->back;

        L->back = L->back->prev;
        L->back->next = NULL;
        freeNode(&N);
        L->length--;
    }    
}

// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void delete(List L) {
    if (L->length <= 0) {
        fprintf( stderr, "List Error: calling delete() on list that is empty.\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List Error: calling delete() on cursor that is NULL.\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor->prev == NULL) {
        deleteFront(L);
    } else if (L->cursor->next == NULL){
        deleteBack(L);
    } else {
        Node N = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&N);
        L->cursor = NULL;
        L->index = -1;
        L->length--;
    }
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
    Node writing = L->front;
    
    while (writing != NULL) {
        fprintf(out, "%d", writing->data);
        writing = writing->next;

        if (writing != NULL) {
            fprintf(out, " ");
        }
        
    }
    
}

// Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
    List new = newList();
    Node copy = L->front;

    while (copy != NULL) {
        append(new, copy->data);
        copy = copy->next;
    }

    return new;
}
