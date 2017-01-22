#include<stdio.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>                                            Traits;
typedef Traits::edge_descriptor                                                                 Edge;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long,
                                                           property<edge_residual_capacity_t, long,
                                                           property<edge_reverse_t, Edge> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type                                              CapacityMap;
typedef property_map<Graph, edge_reverse_t>::type                                               ReverseMap;

int t;

void addEdge(int from, int to, long capacity, CapacityMap& map_capacity, ReverseMap& map_reverse, Graph &g) {
    Edge e, e_rev; bool success;
    tie(e, success) = add_edge(from, to, g);
    tie(e_rev, success) = add_edge(to, from, g);
    map_capacity[e] = capacity;
    map_capacity[e_rev] = 0;
    map_reverse[e] = e_rev;
    map_reverse[e_rev] = e;
}

void do_case() {
    int M, N, K, C;
    scanf("%i %i %i %i", &M, &N, &K, &C);

    int O = M*N; // offset of out-nodes

    if(M == 0 || N == 0) {
        printf("0\n");
        return;
    }

    Graph g(2*O+1);
    CapacityMap map_capacity = get(edge_capacity, g);
    ReverseMap map_reverse = get(edge_reverse, g);

    int source = 2*O;
    int drain = 2*O+1;

    // in-out connections
    for(int v = 0; v < O; ++v) {
        addEdge(v, O+v, C, map_capacity, map_reverse, g);
    }

    // rows
    for(int m = 0; m < M; ++m) {
        // drains
        addEdge(O+m*N, drain, 1, map_capacity, map_reverse, g);
        addEdge(O+(m+1)*N-1, drain, 1, map_capacity, map_reverse, g);

        // up/down
        for(int n = 0; n < N; ++n) {
            if(m != 0) {
                addEdge(O+(m*N)+n, (m-1)*N+n, 1, map_capacity, map_reverse, g);
                addEdge(O+(m-1)*N+n, (m*N)+n, 1, map_capacity, map_reverse, g);
            }
        }
    }

    // columns
    for(int n = 0; n < N; ++n) {
        // drains
        addEdge(N*M+n, drain, 1, map_capacity, map_reverse, g);
        addEdge(N*(2*M-1)+n, drain, 1, map_capacity, map_reverse, g);

        // left/right
        for(int m = 0; m < M; ++m) {
            if(n != 0) {
                addEdge((M*N)+m*N+n, m*N+n-1, 1, map_capacity, map_reverse, g);
                addEdge((M*N)+m*N+n-1, m*N+n, 1, map_capacity, map_reverse, g);
            }
        }
    }

    // knights
    for(int k = 0; k < K; ++k) {
        int m_k, n_k;
        scanf("%i %i", &m_k, &n_k);
        addEdge(source, N*m_k+n_k, 1, map_capacity, map_reverse, g);
    }

    // calculate flow
    long flow = push_relabel_max_flow(g, source, drain);

    printf("%ld\n", flow);

}

int main() {
    scanf("%i", &t);

    while(t--) {
        do_case();
    }

    return 0;
}
