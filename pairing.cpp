#include "pairing.h"

#define INF INT_MAX
#define MAX 300000 // 300000 node max

using namespace std;



// Perform Dijsktra
void dijkstras_pairing(vector< pair<long long, long long> > *adj,int vertices,int src){
    cout << "Starting Dijkstras" << endl;
    unordered_map<int,PairingNode*>found;
    // initialize an empty pairing heap
    PairingHeap dijkstra_pairing; 

    long long nins = 0,nerase = 0, start, stop;
    double tins = 0, terase = 0;
    double tdecrease = 0, ndecrease = 0;
    int start,stop;

    // Build pairing heap with adj and vertices
    int index = 1;
    while(index<=vertices){
        int key;
        if(index==src)
            key = 0;
        else key = INT_MAX;
        start = clock();
        dijkstra_pairing.insert(key,index);
        stop = clock();
        tins += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        index++;
    }
    
    while(!dijkstra_pairing.isEmpty()){
        start = clock(); 
        dijkstra_pairing.deleteMin();
        stop = clock();
        terase += (stop-start)/double(CLOCKS_PER_SEC)*1000;
        nerase++;
        PairingNode *z = dijkstra_pairing.root;
        cout << "Vertex: " << z->index << ", Shortest path length: " << z->key << endl;
        int indx = z->index;
        for(int i=0;i<adj[indx].size();i++){
            int d,w;
            d = adj[indx][i].first;
            w = adj[indx][i].second;
            if(found.find(d)!=found.end())
            {
                PairingNode *x = found[d];
                if(x!=NULL){
                    if(x->key > z->key + w)
                        start = clock(); 
                        decreaseKey(x,z->key + w);
                        stop = clock();
                        tdecrease += (stop-start)/double(CLOCKS_PER_SEC)*1000;
                        ndecrease++;
                }
            }
        }
    }	
    cout << "Per operation time "<< "insert " << tins/nins << " erase " << terase/nerase << " decrease key" << tdecrease/ndecrease << endl;
    cout << "Ending Dijkstras!" << endl;
}

	