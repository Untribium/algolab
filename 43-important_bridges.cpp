#include<stdio.h>
#include<vector>

#include <boost/graph/adjacency_list.hpp>
#include<boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_name_t, int>> Graph;
typedef property_map<Graph, edge_name_t>::type ComponentMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIt;

void do_case(int t) {
    int n, m;
    scanf("%i %i", &n, &m);

    Graph G(n);

    for(int i = 0; i < m; ++i) {
        int u, v;
        scanf("%i %i", &u, &v);

        Edge e;
        bool success;

        tie(e, success) = add_edge(u, v, G);
    }

    ComponentMap map = get(edge_name, G);

    int n_comp = biconnected_components(G, map);

    vector<int> e_comp(n_comp, 0);
    vector<Edge> e_first(n_comp);

    EdgeIt e_beg, e_end;

    for(tie(e_beg, e_end) = edges(G); e_beg != e_end; ++e_beg) {
        e_comp[map[*e_beg]]++;
        e_first[map[*e_beg]] = *e_beg;
    }

    vector<pair<int, int> > bridges;

    for(int i = 0; i < n_comp; ++i) {
        if(e_comp[i] == 1) {
            int u = source(e_first[i], G);
            int v = target(e_first[i], G);

            bridges.push_back(make_pair(min(u, v), max(u, v)));
        }
    }

    sort(bridges.begin(), bridges.end());

    printf("%lu\n", bridges.size());

    for(pair<int, int> b : bridges) {
        printf("%i %i\n", b.first, b.second);
    }
}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }

    return 0;
}
