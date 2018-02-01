#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include<boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>                Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_capacity_t, int> > > > >                          Graph;

typedef graph_traits<Graph>::edge_descriptor                        Edge;
typedef property_map<Graph, edge_weight_t>::type                    WeightMap;
typedef property_map<Graph, edge_capacity_t>::type                  CapacityMap;
typedef property_map<Graph, edge_reverse_t>::type                   ReverseMap;

void flow_edge(int u, int v, int w, int c, WeightMap &mw, CapacityMap &mc, ReverseMap &mi, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    mw[e] = w; mw[r] = -w;
    mc[e] = c; mc[r] = 0;
    mi[e] = r; mi[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, S;
        cin >> N >> M >> S;

        Graph g(S+M+N+2);
        WeightMap mw = get(edge_weight, g);
        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mi = get(edge_reverse, g);

        vector<int> l(S);

        for(int is = 0; is < S; ++is) {
            cin >> l[is];

            flow_edge(S+M+N, is, 0, l[is], mw, mc, mi, g);
        }

        vector<int> a(S, 0);

        for(int im = 0; im < M; ++im) {
            int rs;
            cin >> rs;

            a[rs-1]++;

            flow_edge(rs-1, S+im, 0, 1, mw, mc, mi, g);
        }

        for(int in = 0; in < N; ++in) {
            for(int im = 0; im < M; ++im) {
                int rb;
                cin >> rb;

                flow_edge(S+im, S+M+in, 100-rb, 1, mw, mc, mi, g);
            }
            flow_edge(S+M+in, S+M+N+1, 0, 1, mw, mc, mi, g);
        }

        int f = 0;
        for(int is = 0; is < S; ++is) f += min(a[is], l[is]);
        f = min(f, N);

        successive_shortest_path_nonnegative_weights(g, S+M+N, S+M+N+1);

        cout << f << " " << 100*f-find_flow_cost(g) << endl;

    }

    return 0;
}
