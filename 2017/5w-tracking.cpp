#include<iostream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property,
    property<edge_weight_t, int> >                  Graph;
typedef property_map<Graph, edge_weight_t>::type    WeightMap;

typedef graph_traits<Graph>::vertex_descriptor      Vertex;
typedef graph_traits<Graph>::edge_descriptor        Edge;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        uint N, M, K, X, Y, V;
        cin >> N >> M >> K >> X >> Y;

        V = N*(K+1);
        Graph g(V);
        WeightMap wg = get(edge_weight, g);

        while(M--) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            for(uint ik = 0; ik <= K; ++ik) {
                Edge e;
                tie(e, ignore) = add_edge(ik*N+a, ik*N+b, g);

                wg[e] = c;

                if(d && ik) {
                    tie(e, ignore) = add_edge((ik-1)*N+a, ik*N+b, g);
                    wg[e] = c;

                    tie(e, ignore) = add_edge((ik-1)*N+b, ik*N+a, g);
                    wg[e] = c;
                }
            }
        }

        vector<int> d(V);

        dijkstra_shortest_paths(g, X, distance_map(
            make_iterator_property_map(d.begin(), get(vertex_index, g))));

        cout << d[K*N+Y] << endl;
    }

    return 0;
}
