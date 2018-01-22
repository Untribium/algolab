#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>        Traits;
typedef Traits::edge_descriptor                             Edge;

typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Edge,
    property<edge_capacity_t, int> > > >                    Graph;

void flow_edge(int u, int v, property_map<Graph, edge_capacity_t>::type &cm, property_map<Graph, edge_reverse_t>::type &rm, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    cm[e] = 1; cm[r] = 0;
    rm[e] = r; rm[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int W, N;
        cin >> W >> N;

        Graph g(2*(W+1));

        property_map<Graph, edge_capacity_t>::type cm = get(edge_capacity, g);
        property_map<Graph, edge_reverse_t>::type rm = get(edge_reverse, g);

        for(int in = 0; in < N; ++in) {
            int u, v;
            cin >> u >> v;

            if(u > v) swap(u, v);

            flow_edge(2*u+1, 2*v, cm, rm, g);
        }

        for(int iw = 0; iw < W+1; ++iw) {
            flow_edge(2*iw, 2*iw+1, cm, rm, g);
        }

        int f = push_relabel_max_flow(g, 1, 2*W);

        cout << f << endl;
    }

    return 0;
}
