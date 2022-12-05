#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct PairingNode* root = NULL; 

struct PairingNode
{
    int key;
    int index;
    PairingNode    *leftChild;
    PairingNode    *nextSibling;
    PairingNode    *parent;

      // make new instance of pairing heap node with two empty pointers when no args given
    PairingNode():
        leftChild(NULL), nextSibling(NULL), parent(NULL) {}

        // make new instance of pairing heap node with assigned child and sibling pointers and key value 
    PairingNode( int key_, int index_, PairingNode *leftChild_, PairingNode *nextSibling_, PairingNode *parent_):
         key(key_), index(index_), leftChild(leftChild_), nextSibling(nextSibling_), parent(parent_) {}

    // function to add child to given pairing heap node
    void addChild(PairingNode *node) {
        if(leftChild == NULL)
            leftChild = node;
        else {
            node->nextSibling = leftChild;
            leftChild = node;
        }
    }
};

// merge two pairing heaps with min value as new root
PairingNode *merge(PairingNode *A, PairingNode *B) {
    if(A == NULL) return B;
    if(B == NULL) return A;
    // maintain min pairing heap by assigning smaller value node as root
    if(A->key < B->key) {
        A->addChild(B);
        B->parent = A;
        return A;
    }
    else {
        B->addChild(A);
        A->parent = B;
        return B;
    }

    return NULL; 
}

//Insert item x into the heap, maintaining heap order  
PairingNode *insert(PairingNode *node, int key, int index)
{
    return merge(node, new PairingNode(key, index, NULL, NULL, NULL));
}

// return boolean if pairing heap is empty 
bool isEmpty(PairingNode *node) {
    return (node == NULL);
}

// Return the smallest item
int findMin(PairingNode *node)
{
    if( isEmpty(node) )
        cout << "The heap is empty" << endl;
    return node->key;
}

//Remove smallest item in heap
PairingNode *deleteMin(PairingNode *node) {
    if(node == NULL || node->nextSibling == NULL)
        return node;
    else {
        PairingNode *A, *B, *newNode;
        A = node;
        B = node->nextSibling;
        newNode = node->nextSibling->nextSibling;

        A->nextSibling = NULL;
        B->nextSibling = NULL;

        return merge(merge(A, B), deleteMin(newNode));
    }

    return NULL; // Unreachable
}

PairingNode *decreaseKey( PairingNode *p, int newVal )
{
    if( p->key < newVal )
        return root;    // newVal cannot be bigger
    p->key = newVal;
    // if p is not root, then have to reorder heap
    if( p != root )
    {
        if( p->nextSibling != NULL )
            p->nextSibling->parent = p->parent;
        if( p->parent->leftChild == p )
            p->parent->leftChild = p->nextSibling;
        else
            p->parent->nextSibling = p->nextSibling;

        p->nextSibling = NULL;
        return merge( root, p );
    }
    return root;
}


struct PairingHeap {
    // pairing heap is just pointer to the root node
    PairingNode *root;
     // function to create new instance of empty pairing heap
    PairingHeap():
        root(NULL) {}

    bool isEmpty(void){
        return ::isEmpty(root);
    }
    int findMin(void){
        return ::findMin(root);
    }
    void deleteMin(void){
        root =  ::deleteMin(root->leftChild);
    }
    void decreaseKey(PairingNode *p, int newVal ){
        root = ::decreaseKey(p, newVal);
    }
    void insert(int key, int index){
        root = ::insert(root, key, index);
    }
    void merge(PairingHeap other) {
        root = ::merge(root, other.root);
    }
};

void dijkstras_pairing(vector< pair<long long, long long> > *adj,int v, int src);