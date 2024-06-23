/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA8
* DictionaryTest.cpp 
* A test client for the Dictionary ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
   Dictionary A;

   std::string D[10] = { "QQHZR","VdVUQ","AmOEk","pYxoy","JTGhD","gMnod",
        "JJDQp","aSEqM","uZzvf","kPeAr" };

   for (int i = 0; i < 10; i++)
        A.setValue(D[i], i);

   cout << "printing out Dictionary: \n"<< A.to_string() << "\n";

   cout << "size: " << A.size() << "\n";

   printf("Is \"pYxoy\" in here? %s\n", A.contains("pYxoy") ? "true" : "false");
   printf("Is \"sleuth\" in here? %s\n", A.contains("sleuth") ? "true" : "false");

   A.setValue("uZzvf", 13);

   cout << "\"uZzvf\"'s new value is: " << A.getValue("uZzvf") << "\n";

   A.remove("JJDQp");
   cout << "print out its preorder: \n" << A.pre_string() << "\n";

   A.begin();
   A.next();

   printf("Is current defined? %s\n", A.hasCurrent() ? "true" : "false");
   cout << "current key: " << A.currentKey() << "\n";

   A.end();
   A.prev();
   cout << "current value: " << A.currentVal() << "\n";

   Dictionary B = A;

   printf("Is A == B? %s\n", A == B ? "true" : "false");

   A.clear();

   return 0;
}