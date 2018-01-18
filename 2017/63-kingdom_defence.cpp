#include<iostream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>    Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_residual_capacity_t, int> > > >       Graph;

typedef Traits::edge_descriptor                         Edge;
typedef Traits::vertex_descriptor                       Vertex;

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

        int L, P;
        cin >> L >> P;

        Graph g(L+2);

        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mr = get(edge_reverse, g);

        int d = 0;

        for(int il = 0; il < L; ++il) {
            int i, o;
            cin >> i >> o;

            flow_edge(L,  il,  i, mc, mr, g);
            flow_edge(il, L+1, o, mc, mr, g);

            d += o;
        }

        for(int ip = 0; ip < P; ++ip) {
            int f, t, c, C;
            cin >> f >> t >> c >> C;

            if(f == t) continue;

            flow_edge(f, t, C-c, mc, mr, g);

            if(c) {
                flow_edge(L, t,   c, mc, mr, g);
                flow_edge(f, L+1, c, mc, mr, g);
                d += c;
            }
        }

        int f = push_relabel_max_flow(g, L, L+1);

        cout << (f >= d ? "yes" : "no") << endl;

    }

    return 0;
}
