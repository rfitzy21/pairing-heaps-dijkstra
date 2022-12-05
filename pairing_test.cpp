#include "pairing.h"

using namespace std;

    // Test program
int main( )
{
    // initialize empty pairing heap pointing to new node
    PairingHeap h;

    int numItems = 10000;
    int i = 69;
    int j;

    for( i = 37; i != 0; i = ( i + 37 ) % numItems )
    {
        h.insert(i, 0);
    }
        
    for( i = 1; i < numItems; i++ )
    {
        int x = h.findMin();
        h.deleteMin();
        if( x != i )
            cout << "Oops! test 1 " << i << " curr min: " << x << endl;
    }
    cout << "Test 1 passed!" << endl;
    PairingHeap h2;

    h2 = h;
    while( !h2.isEmpty( ) )
    {
        int x = h2.findMin();
        h2.deleteMin();
        if( x != ++i )
            cout << "Oops! test 2 " << i << endl;
    }
    cout << "Test 2 passed!" << endl;
    PairingHeap heap1, heap2;
    heap1.insert(4, 1);
    heap1.insert(2, 2);

    heap2.insert(5, 3);
    heap2.insert(-1, 4);

    heap1.merge(heap2);

    if ( heap1.findMin() != -1)
        cout << "Oops! test 3 " << heap1.findMin() << endl;
    cout << "Test 3 passed!" << endl;

    // should change findMin from -1 to -16
    heap1.decreaseKey(heap1.root->leftChild, -16);

    if ( heap1.findMin() != -16)
        cout << "Oops! test 4 " << heap1.findMin() << endl;
    cout << "Test 4 passed!" << endl;

    cout << "Check completed" << endl;
    return 0;


}