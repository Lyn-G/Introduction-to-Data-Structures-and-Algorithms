/********************************************************************************* 
* Lynelle Goh, ljgoh 
* 2023 Winter CSE101 PA8
* Dictionary.cpp 
* BST ADT file
*********************************************************************************/ 
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

// Node constructor
// It's most significant difference from the header file for pa7 is a new Node field
// of type int called color. 
Dictionary::Node::Node(keyType k, valType v) {
    // Node fields
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 1;
    // black = 1
    // red = 2
}

// class constructors & destructors

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil = new Dictionary::Node("nil", -3);
    
    root = nil;
    root->parent = nil;
    current = nil;

    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Dictionary::Node("nil", -3);
    
    root = nil;
    root->parent = nil;
    current = nil;

    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    delete(nil);
}

// Access functions --------------------------------------------------------

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) { // make sure this is right
    if (R != N) {
        // std::cout << R->key << " " << R->val << "\n";
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {

    if (R == nil || R == nullptr) return nil;
    
    while (R->right != nil) {
        R = R->right;
    }

    return R;
}

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {

    if (R == nil || R->key == k) {
        return R;
    } else if (k < R->key) {
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }

}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const { 
    Node *holding = search(root, k);

    if (holding == nil) return false;

    if (holding->key == k) return true;

    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if (contains(k) == false) {
        throw std::logic_error(std::string("Dictionary: getValue(): key \"") + k + std::string("\" does not exist"));
    }

    Node *holding = search(root, k);

    return holding->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current == nullptr || current == nil) {
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (hasCurrent() == false) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }

    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (hasCurrent() == false) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }

    return current->val;
}

// RBT functions 
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    Node *y = N->right; // set y

    // turn y's left subtree into N's right subtree
    N->right = y->left;
    if (y->left != nil) {
        y->left->parent = N;
    }

    // link y's parent to x
    y->parent = N->parent;

    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->left) {
        N->parent->left = y;
    } else {
        N->parent->right = y;
    }

    // put x on y's left
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    // set y
    Node *y = N->left;

    // turn y's right subtree into N's left subtree
    N->left = y->right;

    if (y->right != nil) {
        y->right->parent = N;
    }

    // link y's parent to N
    y->parent = N->parent;
    
    if (N->parent == nil) {
        root = y;
    } else if (N == N->parent->right) {
        N->parent->right = y;
    } else {
        N->parent->left = y;
    }

    // put x on y's right
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
    Node *y;
    // black = 1 ; red = 2

    while (N->parent->color == 2) {
        if (N->parent == N->parent->parent->left) {
            y = N->parent->parent->right;

            if (y->color == 2) {
                N->parent->color = 1;
                y->color = 1;

                N->parent->parent->color = 2;
                N = N->parent->parent;
            } else {
                
                if (N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }

                N->parent->color = 1;
                N->parent->parent->color = 2;
                RightRotate(N->parent->parent);
            }
        } else {
            y = N->parent->parent->left;

            if (y->color == 2) {
                N->parent->color = 1;
                y->color = 1;
                
                N->parent->parent->color = 2;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }

                N->parent->color = 1;
                N->parent->parent->color = 2;
                LeftRotate(N->parent->parent);
            }
        }
    }

    root->color = 1;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    Node *w;

    while (N != root && N->color == 1) {
        if (N == N->parent->left) {
            w = N->parent->right;

            if (w->color == 2) {
                w->color = 1;
                N->parent->color = 2;
                LeftRotate(N->parent);
            }

            if (w->left->color == 1 && w->right->color == 1) {
                w->color = 2;
                N = N->parent;
            } else {
                if (w->right->color == 1) {
                    w->left->color = 1;
                    w->color = 2;
                    RightRotate(w);
                    w = N->parent->right;
                }

                w->color = N->parent->color;
                N->parent->color = 1;
                w->right->color = 1;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            w = N->parent->left;

            if (w->color == 2) {
                w->color = 1;
                N->parent->color = 2;
                RightRotate(N->parent);
                w = N->parent->left;
            }

            if (w->right->color == 1 && w->left->color == 1) {
                w->color = 2;
                N = N->parent;
            } else {
                if (w->left->color == 1) {
                    w->right->color = 1;
                    w->color = 2;
                    LeftRotate(w);
                    w = N->parent->left;
                }

                w->color = N->parent->color;
                N->parent->color = 1;
                w->left->color = 1;
                RightRotate(N->parent);
                N = root;
            }
        }
    }

    N->color = 1;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node *y = N;
    Node *x;
    // black = 1 , red = 2

    int y_original = y->color;

    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y = findMin(N->right);
        y_original = y->color;

        x = y->right;

        if (y->parent == N) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }

        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;

        
    }
    if (y_original == 1) {
            RB_DeleteFixUp(x);
        }
}

// Manipulation procedures -------------------------------------------------

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        if (R->left != nil) {
            postOrderDelete(R->left);
        }

        if (R->right != nil) {
            postOrderDelete(R->right);
        }

        delete(R);
    }

}

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);

    root = nil;
    current = nil;

    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {

    // set the root node if the tree is empty
    if (num_pairs == 0) {
        
        Node *z = new Node (k,v);
        root = z;
        root->parent = nil;
        root->left = nil;
        root->right = nil;
        root->color = 1;

        current = root;

        num_pairs++;
        return;
    }

    // search if k is in our tree
    // Node *holding = search(root, k); 

    // if our search came up with nothing, insert a new node
    // if (holding == nil) {
        
    // following the pseudocode given by Professor Tantalo
    Node *y = nil;
    Node *x = root;

    while (x != nil) {
        y = x;

        if (k == x->key) {
            x->val = v;
            return;
        } else if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    Node *z = new Node (k, v);
    z->parent = y;        

    if (y == nil) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = 2;
    RB_InsertFixUp(z);

    num_pairs++;

}
// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {

    if (R == nil || R == nullptr) return nil;
    
    while (R->left != nil) {
        R = R->left;
    }
    return R;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) { // still don't know
    if (contains(k) == false) {
        throw std::logic_error(std::string("Dictionary: getValue(): key \"") + k + std::string("\" does not exist"));
    }
    
    if (current->key == k) {
        current = nil;
    }
    
    Node *z = search(root, k);
    // Node *x = nil;

    if (z == nil) {
        return;
    }

    RB_Delete(z);
    
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() { // still don't know
    if (num_pairs == 0) return;

    if (num_pairs == 1) {
        current = root;
        return;
    }

    current = root;

    Node *holding = current;
    current = findMin(holding);
    // std::cout << current->key << " " << current->val << "\n";
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() { // still don't know
    if (num_pairs == 0) return;

    if (num_pairs == 1) {
        current = root;
        return;
    }

    current = root;

    Node *holding = current;
    current = findMax(holding);
    // std::cout << current->key << " " << current->val << "\n";
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() { 
    // std::cout << current->val << " \n";

    // check to see if we've reached the end
    Node *ending = findMax(root);

    if (ending == current) {
        current = nil;
        return;
    }

    if (hasCurrent() == false ) {
        
        throw std::logic_error("Dictionary: next(): current undefined");
    }

    Node *x = current;
    if (x->right != nil) {
        current = findMin(x->right);
        return;
    }

    Node *y = x->parent;
    while (y != nil && x == y->right) {
        x = y;
        y = y->parent;
    }

    current = y;
    // std::cout << current->key << " " << current->val << "\n";
    return;

    
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() { 

    // check to see if we've reached the end
    Node *ending = findMin(root);

    if (ending == current) {
        current = nil;
        return;
    }

    if (hasCurrent() == false ) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }

    Node *x = current;

    if (x->left != nil) {
        current = findMax(x->left);
        return;
    } 

    Node* y = x->parent;

    while (y != nil && x == y->left) {
        x = y;
        y = y->parent;
    }

    if (y == nil || y == nullptr) {
        current = nil;
        return;
    }
    
    current = y;
    return;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);

        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";

        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s+= "\n";

        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string words;

    inOrderString(words, root);

    return words;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string words;

    preOrderString(words, root);

    return words;
}


// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    
    std::string first = D.to_string();
    std::string second = this->to_string();
    // std::cout << first << "\n" << second << "\n";

    if (first.compare(second) == 0) return true;

    return false;
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary temp = D;

        std::swap(num_pairs, temp.num_pairs);
        std::swap(current, temp.current);
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
    }

    return *this;
}