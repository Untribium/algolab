#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>                Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_capacity_t, int> > > >                            Graph;

typedef graph_traits<Graph>::edge_descriptor                        Edge;
typedef property_map<Graph, edge_capacity_t>::type                  CapacityMap;
typedef property_map<Graph, edge_reverse_t>::type                   ReverseMap;

void flow_edge(int u, int v, CapacityMap &mc, ReverseMap &mi, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    mc[e] = 1; mc[r] = 0;
    mi[e] = r; mi[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, S, D;
        cin >> N >> M >> S >> D;

        Graph g(2*N+2);
        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mi = get(edge_reverse, g);

        for(int in = 0; in < 2*N; in += 2) {
            flow_edge(in, in+1, mc, mi, g);
        }

        for(int im = 0; im < M; ++im) {
            int ra, rb;
            cin >> ra >> rb;

            flow_edge(2*ra+1, 2*rb, mc, mi, g);
        }

        for(int is = 0; is < S; ++is) {
            int rs;
            cin >> rs;

            flow_edge(2*N, 2*rs, mc, mi, g);
        }

        for(int id = 0; id < D; ++id) {
            int rd;
            cin >> rd;

            flow_edge(2*rd+1, 2*N+1, mc, mi, g);
        }

        int f = push_relabel_max_flow(g, 2*N, 2*N+1);

        cout << f << endl;
    }

    return 0;
}
