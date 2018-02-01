#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int> >                  Graph;

typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef property_map<Graph, edge_weight_t>::type    WeightMap;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int K, N;
        cin >> K;

        N = K*(K+1)/2;

        vector<int> v(N);

        Graph g(N);
        WeightMap mw = get(edge_weight, g);

        for(int ik = 0; ik < K; ++ik) {
            for(int jk = 0; jk <= ik; jk++){
                int in = ik*(ik+1)/2+jk;

                cin >> v[in];

                Edge e;

                if(ik+1 < K) {
                    tie(e, ignore) = add_edge(in+ik+1, in, g); // down left
                    mw[e] = v[in];
                }
                if(ik+1 < K) {
                    tie(e, ignore) = add_edge(in+ik+2, in, g); // down right
                    mw[e] = v[in];
                }
                if(jk > 0) {
                    tie(e, ignore) = add_edge(in-1,    in, g); // left
                    mw[e] = v[in];
                }
                if(jk < ik) {
                    tie(e, ignore) = add_edge(in+1,    in, g); // right
                    mw[e] = v[in];
                }
                if(ik && jk < ik) {
                    tie(e, ignore) = add_edge(in-ik,   in, g); // up left
                    mw[e] = v[in];
                }
                if(ik && jk) {
                    tie(e, ignore) = add_edge(in-ik-1, in, g); // up right
                    mw[e] = v[in];
                }
            }
        }

        vector<int> d1(N), d2(N), d3(N);

        dijkstra_shortest_paths(g, 0,   distance_map(make_iterator_property_map(d1.begin(), get(vertex_index, g))));
        dijkstra_shortest_paths(g, N-K, distance_map(make_iterator_property_map(d2.begin(), get(vertex_index, g))));
        dijkstra_shortest_paths(g, N-1, distance_map(make_iterator_property_map(d3.begin(), get(vertex_index, g))));

        int b = INT_MAX;

        for(int in = 0; in < N; ++in) {
            int c = d1[in]+d2[in]+d3[in]-2*v[in];
            b = b < c ? b : c;
        }

        cout << b << endl;
    }

    return 0;
}
