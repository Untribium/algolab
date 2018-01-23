#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property,
    property<edge_weight_t, int,
    property<edge_capacity_t, int> > >                          UGraph;

typedef graph_traits<UGraph>::edge_descriptor                   UEdge;

typedef adjacency_list_traits<vecS, vecS, directedS>            DTraits;
typedef DTraits::edge_descriptor                                DEdge;

typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, int,
    property<edge_reverse_t, DEdge,
    property<edge_residual_capacity_t, int> > > >               DGraph;

typedef property_map<DGraph, edge_reverse_t>::type              DReverseMap;
typedef property_map<DGraph, edge_capacity_t>::type             DCapacityMap;

void flow_edge(int u, int v, int c, DCapacityMap &mc, DReverseMap &mr, DGraph &g) {
    DEdge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    mc[e] = c; mc[r] = 0;
    mr[e] = r; mr[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T, N, M, S, F;
    cin >> T;

    while(T--) {
        cin >> N >> M >> S >> F;

        UGraph g1(N);

        property_map<Graph, edge_weight_t>::type mwg1 = get(edge_weight, g1);
        property_map<Graph, edge_capacity_t>::type mcg1 = get(edge_capacity, g1);

        for(int im = 0; im < M; ++im) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;

            if(a == b) continue;

            UEdge e;
            tie(e, ignore) = add_edge(a, b, g1);

            mwg1[e] = d; mcg1[e] = c;
        }

        if(!M) {
            cout << 0 << endl;
            continue;
        }

        vector<int> ds(N), df(N);

        dijkstra_shortest_paths(g1, S, distance_map(
            make_iterator_property_map(ds.begin(), get(vertex_index, g1))));

        dijkstra_shortest_paths(g1, F, distance_map(
            make_iterator_property_map(df.begin(), get(vertex_index, g1))));

        int d = ds[F]; // full distance

        DGraph g2(N);
        DCapacityMap mcg2 = get(edge_capacity, g2);
        DReverseMap mrg2 = get(edge_reverse, g2);

        graph_traits<UGraph>::edge_iterator ie, ie_end;
        for(tie(ie, ie_end) = edges(g1); ie != ie_end; ++ie) {
            int u, v;
            u = source(*ie, g1); v = target(*ie, g1);

            if(ds[u] > ds[v]) swap(u, v);

            if(ds[u] + mwg1[*ie] + df[v] == d) {
                flow_edge(u, v, mcg1[e], mcg2, mrg2, g2);
            }
        }

        cout << push_relabel_max_flow(g2, S, F) << endl;
    }

    return 0;
}
