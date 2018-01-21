#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/prim_minimum_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirected>      Graph;

typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;

typedef graph_traits<Graph>::edge_iterator          EdgeIt;

int main() {

    ios_base::sync_sith_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, B;
        cin >> N >> B;

        
    }

    return 0;
}
