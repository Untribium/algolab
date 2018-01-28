#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>        Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_residual_capacity_t, int,
    property<edge_capacity_t, int> > > >                    Graph;

typedef graph_traits<Graph>::edge_descriptor                Edge;
typedef property_map<Graph, edge_capacity_t>::type          CapacityMap;
typedef property_map<Graph, edge_reverse_t>::type           ReverseMap;

void flow_edge(int u, int v, int c, CapacityMap &cm, ReverseMap &rm, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    cm[e] = c; cm[r] = 0;
    rm[e] = r; rm[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, K, L;
        cin >> N >> M >> K >> L;

        Graph g(2*N+2);
        CapacityMap cm = get(edge_capacity, g);
        ReverseMap rm = get(edge_reverse, g);

        for(int ik = 0; ik < K; ++ik) {
            int x;
            cin >> x;
            flow_edge(2*N, x,     1, cm, rm, g); // source to stations
            flow_edge(N+x, 2*N+1, 1, cm, rm, g); // stations to drain
        }

        for(int il = 0; il < L; ++il) {
            int x;
            cin >> x;
            flow_edge(x, N+x, 1, cm, rm, g);
        }

        for(int im = 0; im < M; ++im) {
            int x, y;
            cin >> x >> y;
            flow_edge(x,   y,   INT_MAX, cm, rm, g);
            flow_edge(N+x, N+y, 1,       cm, rm, g);
        }

        int f = push_relabel_max_flow(g, 2*N, 2*N+1);

        cout << f << endl;
    }

    return 0;
}
