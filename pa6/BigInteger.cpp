/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA6
* BigInteger.cpp 
* BigInteger ADT file
*********************************************************************************/ 
#include<iostream>
#include<string>
#include <cstddef>
#include <cmath>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include"List.h"
#include "BigInteger.h"

using namespace std;

const long base = 1000000000 ; // change this to 1000000000
const int power = 9; // change this to 9

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;    // +1 (positive), -1 (negative), 0 (zero)
    List digits; // digits = ()
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) { 

    // check if the string is empty
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    } 

    // check if this is a valid string
    std::string str ("0123456789");
    int k = 0;
    if (s[0] != '+' && s[0] != '-') {
        k = 0;
        // puts("0");
    } else if (s[0] == '+' || s[0] == '-') {
        k = 1;
        
        // check if there's a number after it
        if (!isdigit(str[0])) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    std::size_t ch = s.find_first_not_of(str, k);

    if (ch!=std::string::npos) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   }
    int stop = 0;
    if (s[0] == '+') {
        signum = 1;
        stop = 1;
    } else if (s[0] == '-') {
        signum = -1;
        stop = 1;
    } else {
        signum = 1;
    }

    int parse = s.length() - 1;
    // cout << s[hey - 1] << "\n";

    // move past leading zeroes
    // while (s[parse] == '0') {
    //     parse++;
    // }
    digits.moveBack();
    for (;parse > stop - 1;parse--) {

        // we subtract 48 because ASCII
        long i = int(s[parse]) - 48;
        // std::cout << "before entering into loop" << i << "\n";
        if (power != 1) {

            // divide the base by 10 because we need to add the numbers
            int base_before = 1;
            i = i * (base_before);

            for (int p = 0; p < power - 1; p++) {

                // std::cout << i << "\n";
                parse--;
                
                if (parse == stop -1) break;
                // adding the numbers together
                int num = ((int(s[parse]) - 48) * (base_before * 10));
                i = i + num;
                // std::cout << i << "\n";
                base_before = base_before * 10;
                // std::cout << i << "\n";
            }
            
        } 

        // std::cout << i << "\n";
        digits.insertAfter(i);
    }

    digits.moveFront();
    ListElement getting = digits.moveNext();
    while (digits.position() < digits.length()) {
        if (getting == 0) {
            digits.eraseBefore();
        }

        if (digits.position() >= digits.length()) break;

        getting = digits.moveNext();
    }
    // std::cout << digits << "\n";
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const { // check if this is right
    // using signs for comparisons
    
    // BigInteger is less than N
    if (this->sign() == -1 && N.sign() == 1) return -1;
    // cout << "hey" << "\n";

    // BI greater than N
    if (this->sign() == 1 && N.sign() == -1) return 1;
    // cout << "hey" << "\n";

    List A = this->digits;
    List B = N.digits;

    int A_length = A.length();
    int B_length = B.length();

    if (A_length > B_length) {

        if (this->signum == -1 && N.signum == -1) {
            return -1;
        } else {
            return 1;   
        }
    }
    // cout << "hey" << "\n";

    if (A_length < B_length) {
        if (this->signum == -1 && N.signum == -1) {
            return 1;
        } else {
            return -1;
        }
    }
    // cout << "hey" << "\n";

    if (A_length == 0 && B_length == 0) return 0;

    A.moveFront();
    B.moveFront();

    ListElement A_element = A.moveNext();
    ListElement B_element = B.moveNext();

    // cout << "before" << "\n";

    for (int o = 0; o < A_length || o < B_length; o++) {
        // cout << A_element << " |  " << B_element << "\n";
        if (A_element > B_element) {
            // cout << ">" << "\n";
            if (this->signum == -1 && N.signum == -1) {
                return -1;
            }

            return 1;
        }

        if (A_element < B_element) {
            // cout << "<" << "\n";
            if (this->signum == -1 && N.signum == -1) {
                return 1;
            }
            return -1;
        }

        if (o == A_length - 1 && o == B_length - 1) {
            // cout << "3" << "\n";
            break;
        } else if (o == A_length - 1) {
            // cout << "4" << "\n";

            if (this->signum == -1 && N.signum == -1) {
                return 1;
            } else {
                return -1;
            }

        } else if ( o == B_length - 1) {
            // cout << "5" << "\n";

            if (this->signum == -1 && N.signum == -1) {
                return -1;
            } else {
                return 1;
            }
        }

        A_element = A.moveNext();
        B_element = B.moveNext();
    }

    return 0;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

// negate()
void BigInteger::negate() {
    // If this BigInteger is zero, does nothing, 
    if (signum == 0) return;

    // otherwise reverses the sign of this BigInteger positive <--> negative
    if (signum == -1) {
        signum = 1;
        return;
    } else {
        signum = -1;
        return;
    }
}
// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger G;

    int after_sign = 1;

    // -A + -B
    if (this->signum == -1 && N.signum == -1) {
        after_sign = -1;

    // -A + B
    } else if (this->signum == -1 && N.signum == 1) {
        BigInteger copying_this = *this;
        copying_this.signum = 1;
        G = N.sub(copying_this);

        // check for zeroes
        if (G.digits.length() == 1) {
            G.digits.moveFront();
            ListElement t = G.digits.moveNext();
            
            if (t == 0) G.signum = 0;
        }

        return G;

    // A + -B
    } else if (this->signum == 1 && N.signum == -1) {
        // cout << "this " << *this << "N " << N << "\n";
        BigInteger copying_this = *this;
        BigInteger copying_N = N;
        copying_N.signum = 1;
        G = copying_this.sub(copying_N);
        
        // check for zeroes
        if (G.digits.length() == 1) {
            G.digits.moveFront();
            ListElement t = G.digits.moveNext();
            
            if (t == 0) G.signum = 0;
        }
        return G;
    }

    List A = this->digits;
    List B = N.digits;
    // cout << A << "\n";
    // cout << B << "\n";
    
    A.moveBack();
    B.moveBack();

    ListElement first = A.movePrev();
    ListElement second = B.movePrev();

    // if A or B is a zero 
    if (first == 0) {
        return N;
    } else if (second == 0) {
        return *this;
    }

    int carry = 0;
    long adding = 0;
    while (A.position() >= 0 || B.position() >= 0) {
        // cout << "first = " << first << " second = " << second << " carry = ";
        // cout<< carry << "\n";
        // cout << A.position() << "\n";
        adding = first + second + carry;

        // check if we're over our base
        if (adding >= base) {
            carry = 1;
            adding = adding - base;
        } else {
            carry = 0;
        }

        // cout << adding << "\n";
        
        // cout << G.digits << "\n";
        G.digits.insertAfter(adding);
        
        if (A.position() == 0 || B.position() == 0) break;

        first = A.movePrev();
        second = B.movePrev();
    }

    // if we're still not done with B
    if (A.position() == 0 && B.position() != 0) {
        second = B.movePrev();
        adding = carry + second;
        G.digits.insertAfter(adding);

        while (B.position() > 0) {
            if (B.position() == 0) break;
        
            second = B.movePrev();
            G.digits.insertAfter(second);
        }
        carry = 0;
    }

    // not done with A
    if (A.position() != 0 && B.position() == 0) {
        second = A.movePrev();
        adding = carry + second;
        G.digits.insertAfter(adding);

        while (A.position() > 0) {
            if (A.position() == 0) break;
        
            second = A.movePrev();
            G.digits.insertAfter(second);
        }
        carry = 0;
    }

    // if we still have a carry
    if (carry == 1) {
        G.digits.insertAfter(1);
    }


    G.signum = after_sign;

    return G;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {

    BigInteger G;
    
    int one = this->compare(N);

    int negative_one = 1;

    if (one == -1) negative_one = -1;

    if (one == 0) {
        G.digits.insertAfter(0);
        G.signum = 0;
        return G;
    }

    // -A - -B
    if (this->signum == -1 && N.signum == -1) {
        BigInteger copying_this = *this;
        copying_this.signum = 1;
        BigInteger copying_N = N;
        copying_N.signum = 1;
        G = copying_N.sub(copying_this);

        if (one == -1) G.signum = -1;
        
        return G;

    // -A - B
    } else if (this->signum == -1 && N.signum == 1) {
        BigInteger copying_this = *this;
        copying_this.signum = 1;
        G = copying_this.add(N);

        G.signum = -1;

        // check for zeroes
        if (G.digits.length() == 1) {
            G.digits.moveFront();
            ListElement t = G.digits.moveNext();
            
            if (t == 0) G.signum = 0;
        }

        return G;

    // A - -B
    } else if (this->signum == 1 && N.signum == -1) {
        BigInteger copying_N = N;
        copying_N.signum = 1;
        G = this->add(copying_N);

        // check for zeroes
        if (G.digits.length() == 1) {
            G.digits.moveFront();
            ListElement t = G.digits.moveNext();
            
            if (t == 0) G.signum = 0;
        }

        return G;
    }

    List A, B;
    if (one == 1) {
        A = this->digits;
        B = N.digits;
    } else {
        A = N.digits;
        B = this->digits;
        negative_one = -1;
    }

    A.moveBack();
    B.moveBack();

    ListElement first = A.movePrev();
    ListElement second = B.movePrev();

    int carry = 0;
    long adding = 0;
    while (A.position() >= 0 || B.position() >= 0) {
        // cout << "first = " << first << " second = " << second << " carry = ";
        // cout<< carry << "\n";
        // cout << A.position() << "\n";
        adding = first - second + carry;
        // cout << "adding = " << adding << "\n";

        // check if we're over our base
        if (adding < 0) {
            carry = -1;
            adding = adding + base;
        } else {
            carry = 0;
        }

        // cout << adding << "\n";
        
        // cout << G.digits << "\n";
        G.digits.insertAfter(adding);
        
        if (A.position() == 0 || B.position() == 0) break;

        first = A.movePrev();
        second = B.movePrev();
        // puts("S");
    }

    // if we're still not done with B
    if (A.position() == 0 && B.position() != 0) {
        second = B.movePrev();
        adding = carry + second;
        G.digits.insertAfter(adding);

        while (B.position() > 0) {
            if (B.position() == 0) break;
        
            second = B.movePrev();
            G.digits.insertAfter(second);
        }
        carry = 0;
        // puts("Ss");
    }

    // not done with A
    if (A.position() != 0 && B.position() == 0) {
        second = A.movePrev();
        adding = carry + second;
        G.digits.insertAfter(adding);

        while (A.position() > 0) {
            if (A.position() == 0) break;
        
            second = A.movePrev();
            G.digits.insertAfter(second);
        }
        carry = 0;
        // puts("Sss");
    }

    G.digits.moveFront();
    ListElement deleting_zeroes = G.digits.moveNext();

    while (deleting_zeroes == 0) {
        G.digits.eraseBefore();
        deleting_zeroes = G.digits.moveNext();
    }

    G.signum = negative_one;
    return G;
}

// normalizes list
List normalize(List &L) {
    L.moveBack();

    long c = 0; // initial answer
    // long r = 0; // remainder 
    long answer = 0;

    // cout << "L = " << L << "\n";
    ListElement first = L.movePrev();

    for (int i = 0; i < L.length(); i++) {
        // cout << first << "\n";
        answer = first + c;

        if (answer >= base) {
            c = (answer / base) % base;

            // cout << "carry = " << carry << "\n";

            while (answer >= base) {
                answer = answer % base;
            }

        } else {
            c = 0;
        }

        // cout << "answer = " << answer << "\n";
        // cout << "c = " << c << "\n";
        // cout << "r = " << r << "\n";

        L.setAfter(answer);

        // cout << "L = " << L << "\n";

        if (i == L.length() -1) break;
        first = L.movePrev();
    }

    if (L.position() == 0) {
        if (c != 0) {
            L.moveFront();
            L.insertBefore(c);

            c = 0;
        }
    }
    return L;
}

List sumList(List &A, List &B) {
    List G;
    A.moveBack();
    B.moveBack();

    ListElement first = A.movePrev();
    ListElement second = B.movePrev();

    long carry = 0;
    long adding = 0;

    while (A.position() >= 0 || B.position() >= 0) {
        adding  = first + second + carry;

        if (adding >= base) {
            carry = 1;
            adding = adding - base;
        } else {
            carry = 0;
        }
        
        G.insertAfter(adding);

        if (A.position() == 0 || B.position() == 0) break;

        first = A.movePrev();
        second = B.movePrev();
    }

    // if we're still not done with B
    if (A.position() == 0 && B.position() != 0) {
        second = B.movePrev();
        adding = carry + second;
        G.insertAfter(adding);

        while (B.position() > 0) {
            if (B.position() == 0) break;
        
            second = B.movePrev();
            G.insertAfter(second);
        }
        carry = 0;
    }

    // not done with A
    if (A.position() != 0 && B.position() == 0) {
        second = A.movePrev();
        adding = carry + second;
        G.insertAfter(adding);

        while (A.position() > 0) {
            if (A.position() == 0) break;
        
            second = A.movePrev();
            G.insertAfter(second);
        }
        carry = 0;
    }

    // if we still have a carry
    if (carry == 1) {
        G.insertAfter(1);
    }

    return G;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    // cout << "N = " << N.digits << "\n";
    // cout << " this = " << this->digits << "\n";
    
    BigInteger G;
    BigInteger temp;
    BigInteger P;
    BigInteger newly;

    if (this->signum == 0 || N.signum == 0) {
        G.signum = 0;
        return G;
    }    

    List A, B;
    if (this->digits.length() >= N.digits.length()) {
        A = this->digits;
        B = N.digits;
    } else {
        A = N.digits;
        B = this->digits;
    }
    
    // List temp_list = temp.digits;
    List G_list = G.digits;
    List P_list = P.digits;

    int A_len = A.length();
    int B_len = B.length();
    int c = 0;

    B.moveBack();
    A.moveBack();

    ListElement first;
    ListElement second= B.movePrev();

    long answer = 0;
    for (int i = 0; i < B_len; i++, c++) {
        A.moveBack();
        first = A.movePrev();
        
        for (int o = 0; o < A_len; o++) {
            
            answer = first * second;

            temp.digits.insertAfter(answer);

            if (o == A_len - 1) break;

            first = A.movePrev();
        }
        // cout << "Before  " << temp.digits << "\n";
        normalize(temp.digits);
        // cout << "After " << temp.digits << "\n";

        // adding zeroes for each multiplication counter
        for (int o = 0; o < c; o++) {
            temp.digits.moveBack();
            temp.digits.insertAfter(0);
        }
        // cout << "temp = " << temp.digits << "\n";
        G.digits = temp.digits;
        // cout << "G = " << G.digits << "\n";

        if (P.signum == 0) {
            P.digits = temp.digits;
            P.signum = 1;
            G.signum = 1;
        } else {
            // cout << "P before adding = " << P << "\n";
            P.digits = sumList(G.digits, P.digits);
            // cout << "P = " << P << "\n";
            // we normalize twice in multiply because it takes forever to run
            normalize(P.digits);
            // cout << "P after normalize = " << P.digits << "\n";
        }
        
        // cout << "P = " << P << "\n";
        

        if (i == B_len - 1) break;
        
        second = B.movePrev();
        temp.digits.clear();
    }
    
    
    P.signum = this->signum * N.signum;
    return P;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {

    std::string s = "";

    if (signum == -1) {
        s = s + "-";
    } else if (signum == 0) {
        s = s + "0";
        return s;
    }
    // cout << digits << "\n";
    digits.moveFront();
    // cout << "length = " << digits.length() << "\n";
    ListElement element = digits.moveNext();
    int digits_pos = digits.position();
    int digits_len = digits.length();
    while (digits_pos <= digits_len) {
        
        
        int base_before = base;
        
        if (element == 0 && digits_len != 1) {

            for (int i = 1; i < power; i++) {
                s = s + "0";
            }
        } else if (element - (base / 10) < 0 && digits_pos!= 1) { 
            while (element - (base_before / 10) < 0) {
                s = s + "0";
                base_before = base_before / 10;
            }
            s = s + std::to_string(element);
        } else {
            s = s + std::to_string(element);
        }

        if (digits_pos == digits_len) break;
        // cout << element << "\n";
        element = digits.moveNext();
        digits_pos = digits.position();
       
    }

    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }

    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) return true;

    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int eq = A.compare(B);

    if (eq == 0 || eq == -1) return true;

    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    int eq = A.compare(B);

    if (eq == 1) return true;

    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int eq = A.compare(B);

    if (eq == 0 || eq == 1) return true;

    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return (A.add(B));
    
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return (A.sub(B));
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return (A.mult(B));
    
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A= A.mult(B);
    return A;
}
