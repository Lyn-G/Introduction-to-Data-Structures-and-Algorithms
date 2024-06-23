/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA5
* ListTest.cpp 
* Test client for List ADT
*********************************************************************************/ 
#include<iostream>
#include<string>
#include<stdexcept>
#include<cstdio>
#include"List.h"

using namespace std;

int main(){

  List A;

  A.insertAfter(90);
  A.insertAfter(4);
  A.insertAfter(90);
  A.insertAfter(92);
  A.insertAfter(64);
  A.insertBefore(93);
  A.insertBefore(44);
  A.insertBefore(12);
  A.insertBefore(2);

  cout << "A = " << A << "\n";

  A.cleanup();
  cout << "after cleanup(): A = " << A << "\n";
  cout << "back: " << A.back() << "\t\t";
  cout << "front: " << A.front() << "\n";
  cout << "length: " << A.length() << "\t";
  cout << "position: " << A.position() << "\n";
  cout << "peek at the next element: " << A.peekNext() << "\t";
  cout << "peek at the element behind us: " << A.peekPrev() << "\n";

  List B = List(A);
  cout << "copied A to B, do they equal? \t" << B.equals(A) << "\n";

  A.moveFront();
  cout << "moved to the front, then go next: " << A.moveNext() << "\n";

  B.moveBack();
  cout << "moved to the back, then go prev: " << B.movePrev() << "\n";

  A.setAfter(151);
  cout << "setAfter(), then moveNext(): " << A.moveNext() << "\n";

  B.setBefore(66);
  cout << "setBefore(), then movePrev(): " << B.movePrev() << "\n";

  A.eraseAfter();
  cout << "after using eraseAfter(): A = " << A << "\n";

  B.eraseBefore();
  cout << "after using eraseBefore(): B = " << B << "\n";

  cout << "where is 47 in A? \t" << A.findNext(47) << "\n";
  cout << "where is 2 in B? \t" << B.findPrev(2) << "\n";

  List C = A.concat(B);
  cout << "concat(): C = " << C << "\n";

  B.clear();
  cout << "clear and print out: B = " << B << "\n";

  return 0;
}