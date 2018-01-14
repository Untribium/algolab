#include<iostream>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property,
    property<edge_weight_t, int> >                   Graph;

typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;

typedef property_map<Graph, edge_weight_t>::type    WeightMap;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {

        long long V, E, S, A, B;
        cin >> V >> E >> S >> A >> B;

        Graph g(V);
        WeightMap wg = get(edge_weight, g);

        vector<vector<pair<Edge, int> > > w(S);

        boost::unordered_map<Edge, int> m;

        while(E--) {

            int u, v;
            cin >> u >> v;

            Edge e;

            tie(e, ignore) = add_edge(u, v, g);

            for(auto &ew : w) {

                int c;
                cin >> c;

                ew.emplace_back(e, c);
            }

            m.emplace(e, 100000);
        }

        while(S--) {
            int dump;
            cin >> dump;
        }

        for(unsigned int iw = 0; iw < w.size(); ++iw) {
            auto ew = w[iw];

            for(auto eew : ew) {
                wg[eew.first] = eew.second;
            }

            vector<Edge> t;

            kruskal_minimum_spanning_tree(g, back_inserter(t));

            for(auto et : t) {
                m[et] = min(m[et], wg[et]);
            }
        }

        for(auto em : m) {
            if(em.second == 100000) {
                remove_edge(em.first, g); // remove edge if not in any mst
            } else {
                wg[em.first] = em.second;
            }
        }

        vector<int> d(V);

        dijkstra_shortest_paths(g, vertex(A, g), distance_map(&d[0]));

        cout << d[B] << endl;
    }

    return 0;
}
