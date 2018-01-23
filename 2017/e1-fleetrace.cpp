#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include<boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>    Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int,
    property<edge_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_residual_capacity_t, int> > > > >     Graph;

typedef graph_traits<Graph>::edge_descriptor            Edge;

void flow_edge(int u, int v, int w,
        property_map<Graph, edge_weight_t>::type &wm,
        property_map<Graph, edge_capacity_t>::type &cm,
        property_map<Graph, edge_reverse_t>::type &rm,
        Graph &g) {

    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    rm[e] = r; rm[r] = e;
    wm[e] = w; wm[r] = -w;
    cm[e] = 1; cm[r] = 0;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int B, S, P, N;
        cin >> B >> S >> P;

        N = B+S;

        Graph g(N+2);

        property_map<Graph, edge_weight_t>::type wm = get(edge_weight, g);
        property_map<Graph, edge_capacity_t>::type cm = get(edge_capacity, g);
        property_map<Graph, edge_reverse_t>::type rm = get(edge_reverse, g);

        for(int ip = 0; ip < P; ++ip) {

            int b, s, c;
            cin >> b >> s >> c;

            flow_edge(b, B+s, 50-c, wm, cm, rm, g);
        }

        for(int ib = 0; ib < B; ++ib) {
            flow_edge(N,  ib,   0, wm, cm, rm, g);
            flow_edge(ib, N+1, 50, wm, cm, rm, g);
        }

        for(int is = 0; is < S; ++is) {
            flow_edge(B+is, N+1, 0, wm, cm, rm, g);
        }

        successive_shortest_path_nonnegative_weights(g, N, N+1);
        int c = find_flow_cost(g);

        cout << (B*50-c) << endl;
    }

    return 0;
}
