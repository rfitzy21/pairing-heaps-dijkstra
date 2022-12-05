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

using namespace std;
 
struct BHeapNode 
{ 
    pair<int,int> data; 
    int degree; 
    BHeapNode *parent, *child, *sibling; 

}; 

struct BHeap 
{ 
    list<BHeapNode*> arr; 
}; 

void adjust(struct BHeap *heap);
list<BHeapNode*> removeMin(struct BHeap *heap,struct BHeapNode *tree);
BHeapNode* getMin(struct BHeap *heap);
vector<long long> dijkstra_binomial(list< pair<long long, long long> > *adj,long long v,long long src);
void display_binomial(vector<long long> dist, long long v);
