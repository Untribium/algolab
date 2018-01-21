#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
    no_property,
    property<edge_weight_t, int> >                  Graph;

typedef graph_traits<Graph>::edge_iterator          EdgeIt;
typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;

typedef property_map<Graph, edge_weight_t>::type    WeightMap;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, B;
        cin >> N >> B;

        Graph g(N);
        WeightMap wm = get(edge_weight, g);

        for(int in = 0; in < N-1; ++in) {
            for(int jn = in+1; jn < N; ++jn) {
                int c;
                cin >> c;

                Edge e;
                tie(e, ignore) = add_edge(in, jn, g);

                wm[e] = c;
            }
        }

        vector<Edge> t;

        kruskal_minimum_spanning_tree(g, back_inserter(t));

        vector<vector<pair<int, int> > > b(N, vector<pair<int, int> >(N, make_pair(0, 0))); // edges
        vector<vector<int> > a(N);

        int w = 0, r = INT_MAX;

        for(Edge et : t) {
            int u = source(et, g), v = target(et, g);

            b[u][v].first = wm[et]; a[u].push_back(v);
            b[v][u].first = wm[et]; a[v].push_back(u);

            w += wm[et];
        }

        for(int in = 0; in < N; ++in) {
            vector<bool> v(N, false);
            queue<pair<int, int> > q;

            q.emplace(in, 0);

            while(q.size()) {
                int fq, sq;
                tie(fq, sq) = q.front();
                q.pop();

                v[fq] = true;
                b[in][fq].second = sq;

                for(auto eq : a[fq]) {
                    if(!v[eq]) {
                        q.emplace(eq, max(sq, b[fq][eq].first));
                    }
                }
            }
        }

        EdgeIt ei, ei_end;
        for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
            int u = source(*ei, g), v = target(*ei, g);
            if(!b[u][v].first) {
                r = min(wm[*ei]-b[u][v].second, r);
            }
        }

        cout << w+r << endl;
    }

    return 0;
}
