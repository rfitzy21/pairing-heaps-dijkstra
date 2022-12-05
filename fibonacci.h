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
 
//Node Structure
struct Node{
	bool mark;	      // Whether the node has lost a child since 
		     	      // it was made child of another node.
	int index;	      // Index of the vertex
	int key;      	      // Value of the node
	int degree;           // Degree of the node
	Node *parent;         // Parent Pointer
	Node *left, *right;   // Siblings
	Node *child;	      // Child Pointer
};



Node* createnode(int key,int index);
Node* fib_heap_search(int key);
void fib_heap_insert(int key,int index);
Node* fib_heap_extract_min();
void consolidate();
void fib_heap_link(Node *y,Node *x);
void cut(Node *x,Node *y);
void cascading_cut(Node *y);
void fib_heap_decrease_key(int x_key,int k);
void shortest_path_length(vector< pair<int, int> > *adj,int v, int src);