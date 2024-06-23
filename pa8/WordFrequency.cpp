/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA8
* WordFrequency.cpp 
* Client program
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
    // read in each line of a file ✓
    // parse the words on each line ✓
    // convert each word to all lowercase ✓
    // place it (as key) in a Dictionary
    // the number of times a given word is encounter will also be stared (as value)

    // as program is reading in words, use contain() to check if word is present
    // if it's a new word, use setValue()
    // if it already exists, use getValue()

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
    
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    int increase = 0;
    size_t begin, end, len;
    string line;
    string token;
    Dictionary D;

   // read each line of input file, then count the amount tokens 
   while( getline(in, line) )  {
      len = line.length();
      
      // get tokens in this line
      token = "";

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
        transform(token.begin(), token.end(), token.begin(), ::tolower);

        if (D.contains(token) == true) {
            increase = D.getValue(token);
            increase++;
        } else {
            increase = 1;
        }

        D.setValue(token, increase);

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }

   out << D.to_string() << "\n"; // don't think so
    
    // close files
    in.close();
    out.close();

    return 0;
}