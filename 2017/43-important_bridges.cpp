#include<iostream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

typedef graph_traits<Graph>::edge_descriptor    Edge;
typedef graph_traits<Graph>::vertex_descriptor  Vertex;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        unsigned int V, E;
        cin >> V >> E;

        Graph g(V+E);
        vector<pair<int, int> > p;

        for(unsigned int ie = 0; ie < E; ++ie) {
            int u, v;
            cin >> u >> v;

            add_edge(u, V+ie, g);
            add_edge(V+ie, v, g);

            p.emplace_back(min(u, v), max(u, v));
        }

        vector<Vertex> a;

        articulation_points(g, back_inserter(a));

        vector<pair<int, int> > b;

        for(Vertex ea : a) {
            if(ea >= V) {
                b.push_back(p[ea-V]);
            }
        }

        sort(b.begin(), b.end());

        cout << b.size() << endl;

        for(auto eb : b) {
            cout << eb.first << " " << eb.second << endl;
        }
    }

    return 0;
}
