/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA1
* ListTest.c 
* Test client for List ADT 
*********************************************************************************/ 

#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include"List.h"

// Create your own test client for the List ADT called ListTest.c, and submit it with this
// project. It should contain your own tests of all ADT operations. 
int main(int argc, char* argv[]){

    List A = newList();
    List B = newList();
    List C = newList();
    List D = NULL;

    append(A, 3);
    append(A, 5);
    append(A, 9);
    append(A, 10);
    append(A, 13151);
    prepend(A, 888);
    prepend(A, 6544);

    append(B, 9411);
    append(B, 9418);
    append(B, 94199);
    prepend(B, 2493);
    prepend(B, 888);

    puts("printing out List A:");
    printList(stdout,A);
    puts("");
    puts("printing out List B:");
    printList(stdout, B);
    puts("");

    moveFront(A);
    moveBack(B);

    printf("A's front value using get(): %d\n", get(A));
    printf ("A's front value using front(): %d\n", front(A));

    printf("List A's length is: %d\n", length(A));
    printf("List A's index is at: %d\n", index(A));

    moveNext(A);
    moveNext(A);
    movePrev(B);

    printf("List B's index is at: %d\n", index(B));
    printf("List B's back element is: %d\n", back(B));

    insertBefore(A, 7);
    insertAfter(B, 988);

    puts("printing out List A:");
    printList(stdout,A);
    puts("");
    puts("printing out List B:");
    printList(stdout, B);
    puts("");

    set(A, 123);
    set(B, 8);

    moveFront(B);
    movePrev(A);

    deleteFront(A);
    deleteBack(B);

    puts("printing out List A:");
    printList(stdout,A);
    puts("");
    puts("printing out List B:");
    printList(stdout, B);
    puts("");

    printf("Does List A equal List B? %s\n", equals(A,B)?"true":"false");

    clear(A);
    freeList(&A);
    freeList(&B);

    // use delete and copy
    append(C, 1);
    prepend(C, 2);
    prepend(C, 3);

    D = copyList(C);

    // (condition) ? result_if_true : result_if_false
    printf("Does List C equal List D? %s\n", equals(C,D)?"true":"false");

    moveFront(C);
    moveNext(C);

    delete(C);

    printf("Does List C equal List D? %s\n", equals(C,D)?"true":"false");

    puts("printing out List C:");
    printList(stdout,C);
    puts("");
    puts("printing out List D:");
    printList(stdout, D);
    puts("");

    freeList(&C);
    freeList(&D);

    return 0;
}