/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA4
* Matrix.c 
* File contains all Matrix ADT functions
*********************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "List.h"

// entire Entry ADT
typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

Entry newEntry(int column, double value) {
    Entry e = malloc(sizeof(Entry));
    e->column = column;
    e->value = value;
    return e;
}

void freeEntry(Entry *e) {
    free(*e);
    *e = NULL;
}

typedef struct MatrixObj {
    int size;
    int NNZ;
    List *entries;
} MatrixObj;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix m = malloc(sizeof(MatrixObj));
    m->entries = malloc (sizeof(List) * n);
    for (int i = 0; i < n; i++) {
        m->entries[i] = newList();
    }

    m->size = n;
    m->NNZ = 0;
    return (m);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    List l;

    if (pM != NULL && (*pM) != NULL) {
        makeZero(*pM);
        for (int i = 0; i < (*pM)->size; i++) {
            l = (*pM)->entries[i];
            freeList(&l);
            l = NULL;
        }
    }
    free((*pM)->entries);
    free(*pM);
    *pM = NULL;
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    List la;
    List lb;
    Entry ea;
    Entry eb;

    if (A->size != B->size) {
        return 0;
    }

    for (int i = 0; i < A->size; i++) {
        la = A->entries[i];
        lb = B->entries[i];

        if (length(la) != length(lb)) return 0;

        for (moveFront(la), moveFront(lb); index(la) != -1; moveNext(la), moveNext(lb)) {
            ea = (Entry)get(la);
            eb = (Entry)get(lb);

            if (ea->column != eb->column) return 0;

            if (ea->value != eb->value) return 0;
        }
    }

    return 1;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    List l;
    Entry e;

    for (int i = 0; i < M->size; i++) {
        l = M->entries[i];

        for(moveFront(l); index(l) != -1; moveNext(l)) {
            e = (Entry)get(l);
            freeEntry(&e);
        }
        clear(l);
        M->NNZ = 0;
    }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (1 > i || i > size(M)) {
        fprintf( stderr, "Matrix Error: calling changeEntry() with an invalid row number.\n");
        exit(EXIT_FAILURE);
    }

    if (1 > j || j > size(M)) {
        fprintf( stderr, "Matrix Error: calling changeEntry() with an invalid column number.\n");
        exit(EXIT_FAILURE);
    }

    List l = M->entries[i-1];
    Entry e;

    // 0 means delete
    if (x == 0) {
        for (moveFront(l); index(l) >= 0; moveNext(l)) {
            if (((Entry)get(l))->column == j) {
                e = (Entry)get(l);
                freeEntry(&e);
                delete(l);
                M->NNZ--;
            
            }
        }
    } else {
        moveFront(l);
        while (index(l) != -1) {
            e = (Entry)get(l);
            
            if (e->column == j) {
                e->value = x;
                break;
            }  else {
                // insertion sort
                if (e->column > j) {
                    insertBefore(l, newEntry(j, x));
                    moveNext(l);
                    M->NNZ++;
                    break;
                } else if (e->column < j) {
                    moveNext(l);
                    if (index(l) == -1) {
                        append(l, newEntry(j,x));
                        M->NNZ++;
                        break;
                    }
                } 
            }
        }

        if (length(l) == 0 && index(l) == -1) {
            append(l, newEntry(j, x));
            M->NNZ++;
        }
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    Matrix m = newMatrix(A->size);
    List lm;
    List la;
    Entry e;

    for (int i = 0; i < A->size; i++) {
        lm = m->entries[i];
        la = A->entries[i];

        for (moveFront(la); index(la) != -1; moveNext(la)) {
            e = (Entry)get(la);
            append(lm, newEntry(e->column, e->value));
        }
    }

    m->NNZ = A->NNZ;
    return m;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    Matrix m = newMatrix(A->size);
    List la;
    List lm;
    Entry e;

    for (int i = 0; i < A->size ; i++) {
        la = A->entries[i];
        
        for (moveFront(la); index(la) != -1; moveNext(la)) {
            e = (Entry)get(la);
            lm = m->entries[e->column - 1];
            append(lm, newEntry(i+1, e->value));
        }
    }
    m->NNZ = A->NNZ;
    return m;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    Matrix m = copy(A);
    List lm;
    Entry e;

    if (x == 0) {
        makeZero(m);
    } else {
        for (int i = 0; i < A->size; i++) {
            lm = m->entries[i];

            for (moveFront(lm); index(lm) != -1; moveNext(lm)) {
                e = ((Entry)get(lm));
                e->value *= x;
            }
        }
    }
    
    return m;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    List la;
    List lb;
    List lm;
    Entry ea;
    Entry eb;
    double add;

    if (size(A) != size(B)) {
        fprintf( stderr, "Matrix Error: calling sum() with matricies with two different sizes.\n");
        exit(EXIT_FAILURE);
    }

    if (equals(A, B) == 1) {
        Matrix scaled = scalarMult(2, A);
        return scaled;
    }

    Matrix m = newMatrix(size(A));

    for (int i = 0; i < A->size; i++) {
        la = A->entries[i];
        lb = B->entries[i];
        lm = m->entries[i];

        for (moveFront(la), moveFront(lb); index(la) != -1 && index(lb) != -1;) {
            // printf("A: %d B:%d\n", index(la), index(lb));
            ea = (Entry)get(la);
            eb = (Entry)get(lb);

            if (ea->column == eb->column) {
                add = ea->value + eb->value;
                
                if (add != 0.0) {
                    append(lm, newEntry(ea->column, add));
                    m->NNZ++;
                }

                moveNext(la);
                moveNext(lb);
            } else if( ea->column < eb->column) {
                add = ea->value;
                append(lm, newEntry(ea->column, add));
                m->NNZ++;

                moveNext(la);
            } else if (ea->column > eb->column) {
                add = eb->value;
                append(lm, newEntry(eb->column, add));
                m->NNZ++;

                moveNext(lb);
            } // end of if-statement
        } // end of nested for-loop

        for(;index(la) != -1; moveNext(la)) {
            ea = (Entry)get(la);
            add = ea->value;
            append(lm, newEntry(ea->column, add));
            m->NNZ++;
        } // end of for-loop

        for(;index(lb) != -1; moveNext(lb)) {
            eb = (Entry)get(lb);
            add = eb->value;
            append(lm, newEntry(eb->column, add));
            m->NNZ++;
        } // end of for-loop
    } // end of first for-loop

    return m;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf( stderr, "Matrix Error: calling diff() with matricies with two different sizes.\n");
        exit(EXIT_FAILURE);
    }

    List la;
    List lb;
    List lm;
    Entry ea;
    Entry eb;
    double add;

    Matrix m = newMatrix(size(A));

    if (equals(A, B) == 1) {
        return m;
    }

    for (int i = 0; i < A->size; i++) {
        la = A->entries[i];
        lb = B->entries[i];
        lm = m->entries[i];

        for (moveFront(la), moveFront(lb); index(la) != -1 && index(lb) != -1;) {
            // printf("A: %d B:%d\n", index(la), index(lb));
            ea = (Entry)get(la);
            eb = (Entry)get(lb);

            if (ea->column == eb->column) {
                add = ea->value - eb->value;

                if (add != 0.0) {
                append(lm, newEntry(ea->column, add));
                m->NNZ++;
                }

                moveNext(la);
                moveNext(lb);
            } else if( ea->column < eb->column) {
                add = ea->value;
                append(lm, newEntry(ea->column, add));
                m->NNZ++;

                moveNext(la);
            } else if (ea->column > eb->column) {
                add = 0.0 - eb->value;
                append(lm, newEntry(eb->column, add));
                m->NNZ++;

                moveNext(lb);
            } // end of if-statement
        } // end of nested for-loop

        for(;index(la) != -1; moveNext(la)) {
            ea = (Entry)get(la);
            add = ea->value;
            append(lm, newEntry(ea->column, add));
            m->NNZ++;
        } // end of for-loop

        for(;index(lb) != -1; moveNext(lb)) {
            eb = (Entry)get(lb);
            add = 0.0 - eb->value;
            append(lm, newEntry(eb->column, add));
            m->NNZ++;
        } // end of for-loop
    } // end of first for-loop
    return m;

}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf( stderr, "Matrix Error: calling product() with matricies with two different sizes.\n");
        exit(EXIT_FAILURE);
    }   

    List la;
    List lb;
    List lm;
    Entry ea;
    Entry eb;
    double add;

    Matrix m = newMatrix(size(A));
    Matrix t = transpose(B);

    // printMatrix(stdout, A);
    // printMatrix(stdout, t);

    // first loop goes through rows
    for (int k = 0; k < A->size; k++) {

        if (length(A->entries[k]) != 0) {
        // second loop goes through columns
            for (int i = 0; i < m->size; i++) {
                lm = m->entries[k];
                la = A->entries[k];
                lb = t->entries[i];
                add = 0.0;

                if (length(lb) != 0) {
                    for (moveFront(la), moveFront(lb); index(la) != -1 && index(lb) != -1;) {
                        // printf("A: %d B:%d\n", index(la), index(lb));
                        ea = (Entry)get(la);
                        eb = (Entry)get(lb);

                        if (ea->column == eb->column) {
                            add += ea->value * eb->value;

                            moveNext(la);
                            moveNext(lb);
                        } else if( ea->column < eb->column) {

                            moveNext(la);
                        } else if (ea->column > eb->column) {

                            moveNext(lb);
                        } // end of if-statement
                        
                    } // end of nested for-loop
                    if (add != 0.0) {
                        append(lm, newEntry(i+1, add));
                        m->NNZ++;
                    }
                }
            } // end of first for-loop

        }
    }

    freeMatrix(&t);
    return m;

}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    List l;

    for (int i = 0; i < M->size; i++) {
        l = M->entries[i];
        // printf("length %d\n", length(l));
        if (length(l) > 0) {
            fprintf(out, "%d: ", i + 1);
            
            for (moveFront(l); index(l) >= 0; moveNext(l)) {
                fprintf(out, "(%d, %.1f) ", ((Entry)get(l))->column, ((Entry)get(l))->value);
            }
            fprintf(out, "\n");
        }
    }
}