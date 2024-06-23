/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA5
* Shuffle.cpp
* Main program
*********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include "List.h"

using namespace std;

void shuffle(List& D) {

    if (D.length() == 1) {
        return;
    }

    List Shuffling1;
    List Shuffling2;

    // find the half lenths
    D.moveFront();
    int half1 = D.length() / 2;
    int half2 = (D.length() % 2 == 0 ? half1 : half1 + 1);

    ListElement element = D.moveNext();

    // inserting until halfway in for first list
    for (int i = 0; i < half1; i++) {
        Shuffling1.insertBefore(element);
        element = D.moveNext();
    }

    // cout << "A = " << *Shuffling1 << endl;

    // insert into the second list
    for (int k = 0; k < half2; k++) {
        Shuffling2.insertBefore(element);
        
        // check if we're next to the back
        if (k == half2 - 1) break;

        element = D.moveNext();
    }
   
    D.clear();


    // begin the shuffling process
    Shuffling1.moveFront();
    Shuffling2.moveFront();

    element = Shuffling1.moveNext();
    ListElement ele = Shuffling2.moveNext();
    for (int j = 0; j < Shuffling1.length(); j++) {
        D.insertBefore(ele);
        D.insertBefore(element);
        
        // break out if we're near the end
        if (j == Shuffling1.length() - 1) {

            // if half2 has more than half1, add the back value
            if (half1 != half2) {
                ele = Shuffling2.back();
                D.insertBefore(ele);
            }
            break;
        }

        element = Shuffling1.moveNext();
        ele = Shuffling2.moveNext();
    } // end of for-loop

}

int main(int argc, char * argv[]){
   
    int count = atoi(argv[1]);

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        List L;

        for (int k = -1; k < i; k++) {
            L.insertBefore(k + 1);
            // cout << "L = " << *L << endl;
        } // end of nested for-loop

        List LL = List(L);
        shuffle(L);
        int shuffle_count = 1;

        // check for equivalency
        while (!L.equals(LL)) {
            shuffle(L);
            shuffle_count++;
        } // end of if-statement

        cout << " " << i+1 << "\t \t" << shuffle_count << "\n";
    }

    return 0;
}