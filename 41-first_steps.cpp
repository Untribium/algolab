#include<stdio.h>
#include<vector>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

typedef property_map<Graph, edge_weight_t>::type WeightMap;

void do_case() {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph G(n);
    WeightMap w_map = get(edge_weight, G);

    Vertex origin = vertex(0, G);

    for(int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        Edge e;
        bool success;
        tie(e, success) = add_edge(u, v, G);
        w_map[e] = w;
    }

    vector<Edge> edges;

    kruskal_minimum_spanning_tree(G, back_inserter(edges));

    int sum = 0;

    for(Edge e : edges) {
        sum += w_map[e];
    }

    vector<int> dists(n);

    int ld = 0;

    dijkstra_shortest_paths(G, origin, distance_map(&dists[0]));

    for(int dist : dists) {
        ld = max(ld, dist);
    }

    printf("%d %d\n", sum, ld);
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        do_case();
    }
    return 0;
}
