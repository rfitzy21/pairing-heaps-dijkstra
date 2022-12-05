#include "binomial.h"

#define INF INT_MAX
  
BHeapNode *createBHeapNode(pair<long long,long long> key) 
{ 
    BHeapNode *new_node = new BHeapNode; 
    new_node->data = key;
    new_node->parent = NULL; 
    new_node->sibling = NULL; 
    new_node->child = NULL; 
    new_node->degree = 0; 
    return new_node; 
} 

void swap(BHeapNode *b1,BHeapNode *b2)
{
    BHeapNode *a = b1;
    b1 = b2;
    b2 = a;
}
  
BHeapNode *mergeBHeaps(BHeapNode *b1, BHeapNode *b2) 
{ 
    if ((b1->data).first > (b2->data).first)
    {
        swap(b1, b2);
    }
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1; 
} 
  
list<BHeapNode*> unionBHeaps(list<BHeapNode*> l1,list<BHeapNode*> l2) 
{ 
    list<BHeapNode*> _new;
    list<BHeapNode*>::iterator it = l1.begin();
    list<BHeapNode*>::iterator ot = l2.begin();
    while (it!=l1.end() && ot!=l2.end())
    {
        if((*it)->degree <= (*ot)->degree)
        {
            _new.push_back(*it);
            it++;
        }
        else
        {
            _new.push_back(*ot);
            ot++;
        }
    }
    while (it != l1.end())
    {
        _new.push_back(*it);
        it++;
    }
    while (ot!=l2.end())
    {
        _new.push_back(*ot);
        ot++;
    }
    return _new;
} 
  
void insert_binomial(struct BHeap *heap,pair<long long,long long> p) 
{ 
    BHeapNode *tree = createBHeapNode(p);
    list<BHeapNode*> temp;
    temp.push_back(tree);
    heap->arr = unionBHeaps(heap->arr,temp);
    adjust(heap); 
} 

void adjust(struct BHeap *heap)
{
    if (heap->arr.size() <= 1)
        return;
    list<BHeapNode*> new_heap;
    list<BHeapNode*>::iterator it1,it2,it3;
    it1 = it2 = it3 = heap->arr.begin();

    if (heap->arr.size() == 2)
    {
        it2 = it1;
        it2++;
        it3 = heap->arr.end();
    }
    else
    {
        it2++;
        it3=it2;
        it3++;
    }
    while (it1 != heap->arr.end())
    {
        if (it2 == heap->arr.end())
            it1++;
        else if ((*it1)->degree < (*it2)->degree)
        {
            it1++;
            it2++;
            if(it3!=heap->arr.end())
                it3++;
        }
        else if (it3!=heap->arr.end() &&
                (*it1)->degree == (*it2)->degree &&
                (*it1)->degree == (*it3)->degree)
        {
            it1++;
            it2++;
            it3++;
        }
        else if ((*it1)->degree == (*it2)->degree)
        {
            *it1 = mergeBHeaps(*it1,*it2);
            it2 = heap->arr.erase(it2);
            if(it3 != heap->arr.end())
                it3++;
        }
    }
    return;
}

pair<long long, long long> extractMin(struct BHeap *heap)
{
    if(heap->arr.size() == 0)
        return make_pair(-1, -1);
    list<BHeapNode*> new_heap,lo;
    BHeapNode *temp;
    temp = getMin(heap);
    list<BHeapNode*>::iterator it;
    it = heap->arr.begin();
    while (it != heap->arr.end())
    {
        if (*it != temp)
        {
            new_heap.push_back(*it);
        }
        it++;
    }
    lo=removeMin(heap,temp);
    heap->arr = unionBHeaps(new_heap,lo);
    adjust(heap);
    return temp->data;
}
  
list<BHeapNode*> removeMin(struct BHeap *heap,struct BHeapNode *tree)
{
    list<BHeapNode*> tempheap;
    BHeapNode *temp = tree->child;
    BHeapNode *lo;
    while (temp)
    {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        tempheap.push_front(lo);
    }
    return tempheap;
}

BHeapNode* getMin(struct BHeap *heap)
{
    if (heap->arr.size() == 0)
        return NULL;
    list<BHeapNode*>::iterator it = heap->arr.begin();
    BHeapNode *temp = *it;
    while (it != heap->arr.end())
    {
        if (((*it)->data).first < (temp->data).first)
            temp = *it;
        it++;
    }
    return temp;
}

pair<long long, long long> top(struct BHeap *heap)
{
    if(heap->arr.size() == 0)
        return make_pair(-1, -1);

    return getMin(heap)->data;
}

pair<long long, long long> pop(struct BHeap *heap)
{
    if(heap->arr.size() == 0)
        return make_pair(-1, -1);

    pair<long long, long long> BHeapNode = extractMin(heap);
    return BHeapNode;
}

vector<long long> dijkstra_binomial(list< pair<long long, long long> > *adj,long long V,long long src)
{  
    struct BHeap heap;
    long long nins = 0,nerase = 0, start, stop;
    double tins = 0, terase = 0;
    vector<long long> dist(V, INF); 
    start = clock();
    insert_binomial(&heap,make_pair(0, src)); 
    stop = clock();
    tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
    nins++;
    dist[src] = 0; 

    while (top(&heap) != make_pair(static_cast<long long>(-1), static_cast<long long>(-1))) 
    { 
        long long u = top(&heap).second; 
        start = clock(); 
        pop(&heap);
        stop = clock();
        terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        nerase++;
  
        list< pair<long long, long long> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            long long v = (*i).first; 
            long long weight = (*i).second; 
  
            if (dist[v] > dist[u] + weight) 
            { 
                dist[v] = dist[u] + weight; 
		        start = clock(); 
                insert_binomial(&heap,make_pair(dist[v], v)); 
                stop = clock();
                tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
                nins++;
            } 
        } 
    } 
    cout << "Per operation for binomial: "<< "insert " << tins/nins << "ms " << " erase " << terase/nerase << "ms " << endl;
    cout << "# operation for binomial: "<< "insert " << nins << " erase " << nerase << endl;
    return dist;
}


void display_binomial(vector<long long> dist,long long V)
{
    printf("Vertex   Distance from Source\n"); 
    for (long long i = 0; i < V; ++i) 
        printf("%lld \t\t %lld\n", i, dist[i]);
}
