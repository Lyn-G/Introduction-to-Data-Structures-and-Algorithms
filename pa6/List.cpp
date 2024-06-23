/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA6
* List.cpp
* File contains all List ADT functions
*********************************************************************************/ 

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

// Private Constructor

// Node constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors

// Creates new List in the empty state.
List::List() {
    frontDummy = new List::Node(-3);
    backDummy = new List::Node(-33);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    // make this an empty list
    frontDummy = new List::Node(-3);
    backDummy = new List::Node(-33);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L into this List
    Node *load = L.frontDummy->next;

    while (load != L.backDummy) {
        this->insertBefore(load->data);
        load = load->next;
    }
   
    moveFront();
}

// Destructor
List::~List() {
    clear();
    delete (frontDummy);
    delete (backDummy);
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (length() <= 0) {
        throw std::length_error("List: front(): empty list");
    }

    return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (length() <= 0) {
        throw std::length_error("List: back(): empty list");
    }

    return (backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    if (0 > pos_cursor || pos_cursor > num_elements) {
        throw std::length_error("List: calling position() on an invalid position in List.");
    }

    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (position() >= length()) {
        throw std::range_error("List: peekNext(): cursor at back");
    }

    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (position () <= 0) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }

    return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    Node *N = frontDummy->next;
    Node *M = frontDummy->next;
   
    while (N != backDummy) {
        M = N->next;
        delete(N);
        N = M;
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
   
    // check if the position isn't already at 0
    if (pos_cursor > 0) {
       
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
        pos_cursor = 0;
    }
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {

    // printf("before: %d, after: %d\n", beforeCursor->data, afterCursor->data);
    // check if the position isn't already at the back
    if (pos_cursor < num_elements) {
        afterCursor = backDummy;
        beforeCursor = backDummy->prev;
        pos_cursor = num_elements;
       
    }
    // printf("before: %d, after: %d\n", beforeCursor->data, afterCursor->data);
}

// moveNext()
// Advances cursor to next higher position.
// pre: position()<length()
ListElement List::moveNext() {
    if (position () >= length()) {
        throw std::range_error("List: moveNext(): cursor at back");
    }

    if (afterCursor != backDummy) {
        pos_cursor++;

        beforeCursor = afterCursor;

        afterCursor = afterCursor->next;

    }

    // return the list element that was passed over
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position.
// pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) {
        throw std::range_error("List: movePrev(): cursor at front");
    }

    if (beforeCursor != frontDummy) {
        pos_cursor--;
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
    }

    return afterCursor->data;
}

// inserts x after cursor
void List::insertBefore(ListElement x) {

    // cursor is at the back
    if (afterCursor == backDummy) {
       
        Node *N = new Node(x);

        if (num_elements == 0) {
            // puts("length is 0");
            frontDummy->next = N;
            backDummy->prev = N;

            N->next = backDummy;
            N->prev = frontDummy;

            afterCursor->prev = N;
            beforeCursor->next = N;
            beforeCursor = N;

            pos_cursor++;

        } else {
            // puts("at back");
            N->next = backDummy;
            N->prev = beforeCursor;

            backDummy->prev = N;

            afterCursor->prev = N;
            beforeCursor->next = N;
            beforeCursor = N;

            pos_cursor++;
        }

        num_elements++;
    } else {
        // puts("in middle");
        num_elements++;

        Node *M = new Node(x);

        M->prev = beforeCursor;
        M->next = afterCursor;

        beforeCursor->next = M;
        afterCursor->prev = M;
        beforeCursor = M;

        pos_cursor++;
    }
    // printf("before: %d, after: %d\n", beforeCursor->data, afterCursor->data);
}

// insertBefore()
// Inserts x before cursor.
void List::insertAfter(ListElement x) {

    if (beforeCursor== frontDummy) {
        Node *N = new Node(x);

        if (length() == 0) {
            frontDummy->next = N;
            backDummy->prev = N;

            N->next = backDummy;
            N->prev = frontDummy;

            beforeCursor->next = N;
            afterCursor->prev = N;
            afterCursor = N;

            num_elements++;
        } else {
           

            N->prev= frontDummy;
            N->next = afterCursor;

            frontDummy->next = N;

            beforeCursor->next = N;
            afterCursor->prev = N;
            afterCursor = N;

            num_elements++;
           
        }
    } else {
        num_elements++;

        Node *M = new Node(x);

        M->next = afterCursor;
        M->prev = beforeCursor;

        afterCursor->prev = M;
        beforeCursor->next = M;
        afterCursor = M;
       
    }
        // printf("before: %d, after: %d\n", beforeCursor->data, afterCursor->data);

}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::range_error("List: setAfter(): cursor at back");
    }

    Node* N = afterCursor;

    N->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::range_error("List: setBefore(): cursor at front");
    }

    Node* N = beforeCursor;

    N->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    Node *N = afterCursor;

    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;

    afterCursor = afterCursor->next;

    delete(N);
   
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() <= 0) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node *N = beforeCursor;

    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;

    beforeCursor = beforeCursor->prev;

    delete(N);
   
    num_elements--;
    pos_cursor--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {

    if (num_elements == pos_cursor) {
        return -1;
    }

    ListElement found = moveNext();

    while (x != found) {
        if (pos_cursor == num_elements) {
            moveBack();
            return -1;
        }
        found = moveNext();
    }
    return pos_cursor;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {

    if (pos_cursor == 0) {
        return -1;
    }

    ListElement found = movePrev();

    while (x != found) {
        if (pos_cursor == 0) {
            moveFront();
            // printf("before: %d, after: %d\n, front->next: %d\n", beforeCursor->data, afterCursor->data, frontDummy->next->next->data);
            return -1;
        }
        found = movePrev();
    }
    return pos_cursor;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
   
    if (length() == 1 || length() == 0) {
        return;
    }

    Node*first = frontDummy->next;
    Node*second = frontDummy->next;
   
    int i = 1; // counter for the second loop
    int k = 1; // counter for the first loop
    int position = pos_cursor;

    // go through the list to hold the base comparison
    while (first != backDummy) {

        // to make looping faster, set the second node to after first
        // since we have already checked through the first nodes
        second = first->next;
        ListElement first_num = first->data;

        i = k;
        position = pos_cursor;

        // go through the list using the second node to check
        while (second != backDummy) {
            // printf("i: %d, k: %d, position: %d\n", i, k, position);
            ListElement second_num = second->data;

            // check for match
            if (first_num == second_num) {
               
                // fix cursor
                if (i < position) {
                    pos_cursor--;
                   

                    // printf("pos_curs: %d, num: %d\n", pos_cursor, num_elements - 1);
                    if (pos_cursor >= num_elements - 1) {
                        afterCursor = backDummy;
                        beforeCursor = backDummy->prev;
                    } else {
                        afterCursor = beforeCursor;
                        beforeCursor = beforeCursor->prev;
                    }
                   
                }

                // hold onto node for deletion
                Node*third = second->next;

                // change node's arrows before deletion
                second->prev->next = second->next;
                second->next->prev = second->prev;
               
                // printf("beforecursor: %d , aftercursor: %d\n", beforeCursor->data, afterCursor->data);

                delete(second);
                second = third;

               
                num_elements--;
                i++;

            } else {
                second = second->next;
                i++;
            }
           
        }
        first = first->next;
        k++;
    }

}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List J;
    Node *N = this->frontDummy->next;
    Node *M = L.frontDummy->next;

    while ( N != backDummy) {
        // printf("N: %d\n", N->data);
        J.insertBefore(N->data);
        N = N->next;
    }
    while (M != L.backDummy) {
        // printf("M: %d\n", M->data);
        J.insertBefore(M->data);
        M = M->next;
    }
    J.moveFront();
    // printf("%d\n", J.length());
    return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string representation = "(";

    Node *N = frontDummy->next;
    int i = 0;

    while (N != backDummy) {
        representation += std::to_string(N->data);

        if (N->next == backDummy) break;

        representation += ", ";
        N = N->next;
        i++;
    }

    representation += ")";
   
    return representation;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    bool eq = false;
    Node *N = this->frontDummy->next;
    Node *M = R.frontDummy->next;
   
    eq = (this->length() == R.length());

    while (eq == true && (N != backDummy || M != R.backDummy)) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if (this != &L) {
        // make a copy of L
        List temp = L;

        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        // std::swap(frontDummy->next, temp.frontDummy->next);
        std::swap(backDummy, temp.backDummy);
        // std::swap(backDummy->next, temp.backDummy->next);
        std::swap(num_elements, temp.num_elements);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(pos_cursor, temp.pos_cursor);

    }

    return *this;
}
