#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property,
    property<edge_weight_t, int> >             Graph;

typedef graph_traits<Graph>::vertex_descriptor   Vertex;
typedef graph_traits<Graph>::edge_descriptor     Edge;

typedef property_map<Graph, edge_weight_t>::type WeightMap;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {

        int V, E;
        cin >> V >> E;

        Graph g(V);
        WeightMap wg = get(edge_weight, g);

        while(E--) {
            int u, v, w;
            cin >> u >> v >> w;

            Edge e;

            tie(e, ignore) = add_edge(u, v, g);

            wg[e] = w;
        }

        vector<Edge> mst;

        kruskal_minimum_spanning_tree(g, back_inserter(mst));

        int s = 0;

        for(Edge e : mst) {
            s += wg[e];
        }

        cout << s << " ";

        vector<int> dg(V);

        dijkstra_shortest_paths(g, vertex(0, g), distance_map(&dg[0]));

        int d = 0;

        for(int edg : dg) {
            d = max(d, edg);
        }

        cout << d << endl;

    }

    return 0;
}
