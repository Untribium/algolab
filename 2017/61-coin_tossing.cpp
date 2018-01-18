#include<iostream>
#include<vector>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_capacity_t, int,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef Traits::edge_descriptor                             Edge;
typedef Traits::vertex_descriptor                           Vertex;

typedef property_map<Graph, edge_capacity_t>::type          CapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualMap;
typedef property_map<Graph, edge_reverse_t>::type           ReverseMap;

void addEdge(int f, int t, int c, CapacityMap &mc, ReverseMap &mr, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(f, t, g);
    mc[e] = c;

    tie(r, ignore) = add_edge(t, f, g);
    mc[r] = 0;

    mr[e] = r; mr[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        uint P, R;
        cin >> P >> R;

        Graph g(P+2); // one node for each p + source + drain

        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mr = get(edge_reverse, g);

        vector<int> p(P);
        vector<int> i(P); // in degree (boost function won't compile...)
        int q = 0;

        for(uint ir = 0; ir < R; ++ir) {

            int a, b, c;
            cin >> a >> b >> c;

            if(c) {
                p[(c == 1 ? a : b)]++;
            } else {
                addEdge(P, a, 1, mc, mr, g);
                addEdge(a, b, 1, mc, mr, g);
                i[a]++; i[b]++;
                q++;
            }
        }

        bool c = false;
        uint z = 0;

        for(uint ip = 0; ip < P; ++ip) {
            int s;
            cin >> s;

            addEdge(ip, P+1, s-p[ip], mc, mr, g);
            z += s;

            if(p[ip] > s || i[ip] < s-p[ip]) {
                c = true;
            }
        }

        if(c || z != R) {
            cout << "no" << endl; continue;
        }

        int f = push_relabel_max_flow(g, P, P+1);

        cout << (f == q ? "yes" : "no") << endl;
    }

    return 0;
}
