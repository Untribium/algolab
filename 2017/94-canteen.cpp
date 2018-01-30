#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include<boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>                Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_capacity_t, int,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_weight_t, int> > > > >                            Graph;

typedef graph_traits<Graph>::edge_descriptor                        Edge;
typedef property_map<Graph, edge_weight_t>::type                    WeightMap;
typedef property_map<Graph, edge_capacity_t>::type                  CapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type         ResidualMap;
typedef property_map<Graph, edge_reverse_t>::type                   ReverseMap;

void flow_edge(int u, int v, int c, int w, WeightMap &mw, CapacityMap &mc, ReverseMap &mi, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    mw[e] = w; mw[r] = -w;
    mi[e] = r; mi[r] = e;
    mc[e] = c; mc[r] = 0;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        Graph g(2+N);
        WeightMap mw = get(edge_weight, g);
        CapacityMap mc = get(edge_capacity, g);
        ResidualMap mr = get(edge_residual_capacity, g);
        ReverseMap mi = get(edge_reverse, g);

        for(int in = 0; in < N; ++in) {
            int ra, rc;
            cin >> ra >> rc;

            flow_edge(N, in, ra, rc, mw, mc, mi, g);
        }

        int ss = 0;

        for(int in = 0; in < N; ++in) {
            int rs, rp;
            cin >> rs >> rp;

            ss += rs;

            flow_edge(in, N+1, rs, 20-rp, mw, mc, mi, g);
        }

        for(int in = 0; in < N-1; ++in) {
            int rv, re;
            cin >> rv >> re;

            flow_edge(in, in+1, rv, re, mw, mc, mi, g);
        }

        successive_shortest_path_nonnegative_weights(g, N, N+1);

        int f = 0;

        graph_traits<Graph>::out_edge_iterator ie, ie_end;
        for(tie(ie, ie_end) = out_edges(N, g); ie != ie_end; ++ie) {
            f += mc[*ie]-mr[*ie];
        }

        cout << (f == ss ? "possible" : "impossible") << " ";
        cout << f << " " << f*20-find_flow_cost(g) << endl;
    }

    return 0;
}
