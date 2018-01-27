#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include<boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>        Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_capacity_t, int,
    property<edge_residual_capacity_t, int> > > > >         Graph;

typedef graph_traits<Graph>::edge_descriptor                Edge;

void flow_edge(int u, int v, int c, int w,
        property_map<Graph, edge_weight_t>::type &wm,
        property_map<Graph, edge_capacity_t>::type &cm,
        property_map<Graph, edge_reverse_t>::type &rm,
        Graph &g) {

    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    wm[e] = w; wm[r] = -w;
    cm[e] = c; cm[r] = 0;
    rm[e] = r; rm[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, L, Q = 128;
        cin >> N >> M >> L;

        Graph g(N+2);

        property_map<Graph, edge_weight_t>::type wm = get(edge_weight, g);
        property_map<Graph, edge_capacity_t>::type cm = get(edge_capacity, g);
        property_map<Graph, edge_reverse_t>::type rm = get(edge_reverse, g);

        for(int in = 1; in < N; ++in) {
            flow_edge(in-1, in, L, Q, wm, cm, rm, g);
        }

        flow_edge(N,   0,   L, 0, wm, cm, rm, g);
        flow_edge(N-1, N+1, L, 0, wm, cm, rm, g);

        for(int im = 0; im < M; ++im) {
            int rx, ry, rq;
            cin >> rx >> ry >> rq;

            flow_edge(rx, ry, 1, (ry-rx)*Q-rq, wm, cm, rm, g);
        }

        successive_shortest_path_nonnegative_weights(g, N, N+1);

        cout << L*(N-1)*Q-find_flow_cost(g) << endl;
    }

    return 0;
}
