#include<iostream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>    Traits;
typedef Traits::edge_descriptor                         Edge;
typedef Traits::vertex_descriptor                       Vertex;

typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_capacity_t, int,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Edge > > > >                Graph;

typedef property_map<Graph, edge_capacity_t>::type      CapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseMap;

void flow_edge(int f, int t, int c, CapacityMap &mc, ReverseMap &mr, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(f, t, g);
    tie(r, ignore) = add_edge(t, f, g);

    mc[e] = c; mc[r] = 0;
    mr[e] = r; mr[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int I, R, S; // intersections, roads, stores
        cin >> I >> R >> S;

        Graph g(I+1);

        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mr = get(edge_reverse, g);

        for(int is = 0; is < S; ++is) {
            int s;
            cin >> s;

            flow_edge(s, I, 1, mc, mr, g);
        }

        for(int ir = 0; ir < R; ++ir) {
            int f, t;
            cin >> f >> t;

            flow_edge(f, t, 1, mc, mr, g);
            flow_edge(t, f, 1, mc, mr, g);
        }

        int f = push_relabel_max_flow(g, 0, I);

        cout << (f == S ? "yes" : "no") << endl;
    }

    return 0;
}
