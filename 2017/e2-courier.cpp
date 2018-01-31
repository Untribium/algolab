#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>            Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_capacity_t, int> > > >                        Graph;

typedef graph_traits<Graph>::edge_descriptor                    Edge;
typedef property_map<Graph, edge_capacity_t>::type              CapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type     ResidualMap;
typedef property_map<Graph, edge_reverse_t>::type               ReverseMap;

void flow_edge(int u, int v, int c, CapacityMap &mc, ReverseMap &mi, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    mc[e] = c; mc[r] = 0;
    mi[e] = r; mi[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int Z, J, r;
        cin >> Z >> J;

        Graph g(2+Z+J);
        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mi = get(edge_reverse, g);

        for(int iz = 0; iz < Z; ++iz) {
            cin >> r;
            flow_edge(Z+J, iz, r, mc, mi, g);
        }

        vector<int> p(J);
        int sp = 0;

        for(int ij = 0; ij < J; ++ij) {
            cin >> r;

            sp += r;
            flow_edge(Z+ij, Z+J+1, r, mc, mi, g);
        }

        for(int ij = 0; ij < J; ++ij) {
            int rn;
            cin >> rn;

            for(int in = 0; in < rn; ++in) {
                int rz;
                cin >> rz;

                flow_edge(rz, Z+ij, INT_MAX, mc, mi, g);
            }
        }

        int f = push_relabel_max_flow(g, Z+J, Z+J+1);
        
        cout << (sp-f) << endl;
    }


    return 0;
}
