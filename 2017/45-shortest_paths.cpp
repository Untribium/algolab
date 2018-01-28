#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int> >                Graph;

typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef property_map<Graph, edge_weight_t>::type        WeightMap;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, M ,Q;
    cin >> N >> M >> Q;

    int drop;
    for(int in = 0; in < N; ++in) cin >> drop >> drop;

    Graph g(N);
    WeightMap wm = get(edge_weight, g);

    for(int im = 0; im < M; ++im) {
        int a, b, c;
        cin >> a >> b >> c;

        Edge e;
        tie(e, ignore) = add_edge(a, b, g);
        wm[e] = c;
    }

    for(int iq = 0; iq < Q; ++iq) {
        int s, t;
        cin >> s >> t;

        vector<int> d(N);

        dijkstra_shortest_paths(g, s, distance_map(make_iterator_property_map(d.begin(), get(vertex_index, g))));

        if(d[t] == INT_MAX) {
            cout << "unreachable" << endl;
        } else {
            cout << d[t] << endl;
        }
    }
}
