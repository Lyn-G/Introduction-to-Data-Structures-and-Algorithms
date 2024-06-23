/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA6
* Arithmetic.cpp 
* Main program
*********************************************************************************/ 
#include<iostream>
#include<fstream>
#include<string>
#include <cstdio>
#include "List.h"
#include "BigInteger.h"

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

   string number;
   string second_number;
   std::getline(in, number);
   std::getline(in, second_number);
   if (second_number.length() == 0) std::getline(in, second_number);
   // cout << number << " " << second_number << "\n";
   
   BigInteger A = BigInteger(number);
   BigInteger B = BigInteger(second_number);

   out << A  << "\n\n";
   out << B << "\n\n";
   out << A + B << "\n\n";
   out << A - B << "\n\n";
   out << A - A << "\n\n";
   
   BigInteger C = BigInteger("3");
   BigInteger D = BigInteger("2");
   BigInteger E = A * C;
   BigInteger F = B * D;

   out << E - F << "\n\n";
   out << A * B << "\n\n";
   out << A * A << "\n\n";
   out << B * B << "\n\n";

   BigInteger G = BigInteger("9");
   BigInteger H = BigInteger("16");
   BigInteger I = A;

   I *= A;
   I *= A;
   I *= A;

   BigInteger J = B;
   J *= B;
   J *= B;
   J *= B;
   J *= B;

   G *= I;
   H *= J;

   out << G + H << "\n";

   // close files
   in.close();
   out.close();

   return 0;
}