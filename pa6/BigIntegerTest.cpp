/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA6
* BigIntegerTest.cpp 
* Test Client for BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    BigInteger A;
    BigInteger B;
    BigInteger C;
    BigInteger D;

   A = BigInteger("1415461");
   B = A;
   cout << "sign of A = " << A.sign() << "\n";
   cout << "does A equal B? " << A.compare(B) << "\n";

   B.makeZero();
   A.negate();
   cout << "negate = " << A.sign() << "\n";

    B = BigInteger("84515");
   cout << A + A << "\n";
   cout << B - A << "\n";
   D = BigInteger("6");
   cout << D * A << "\n";

   if (D == A) {
    cout << "D and A are equal" << "\n";
   }

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   D += A;
   cout << "D = " << D << "\n";
   D -= A;
   cout << "A = " << A << "\n";

   BigInteger E = BigInteger("35151");
   BigInteger L = BigInteger("155");

   E *= L;
   cout << "E = " << E << "\n";
   E = D * L;
   cout << "E = " << E << "\n";
   
   return EXIT_SUCCESS;
}
