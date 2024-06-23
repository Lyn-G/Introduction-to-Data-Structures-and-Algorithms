/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA7
* Order.cpp 
* Client program
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
    ifstream in;
   ofstream out;

    if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

    std::string character;
    int counter = 0;
    Dictionary A;
    while (std::getline (in, character)){
        counter++;
        A.setValue(character, counter); // most likely this function or search()
    }

    out << A.to_string() << "\n"; // don't think so
    out << A.pre_string() << "\n"; // don't think so

    return 0;
}