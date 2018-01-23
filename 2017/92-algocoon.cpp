#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>        Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_capacity_t, int> > > >                    Graph;

typedef graph_traits<Graph>::edge_descriptor                Edge;
typedef graph_traits<Graph>::vertex_descriptor              Vertex;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M;
        cin >> N >> M;

        Graph g(N);

        property_map<Graph, edge_capacity_t>::type mc = get(edge_capacity, g);
        property_map<Graph, edge_reverse_t>::type mi = get(edge_reverse, g);
        property_map<Graph, edge_residual_capacity_t>::type mr = get(edge_residual_capacity, g);

        for(int im = 0; im < M; ++im) {

            int a, b, c;
            cin >> a >> b >> c;

            Edge e, r;

            tie(e, ignore) = add_edge(a, b, g);
            tie(r, ignore) = add_edge(b, a, g);

            mc[e] = c; mc[r] = 0;
            mi[e] = r; mi[r] = e;
        }

        int bf = INT_MAX, f;
        pair<int, int> bp;

        for(int in = 0; in < N; ++in) {
            f = push_relabel_max_flow(g, in, (in+1)%N);

            if(f >= bf) continue;

            bf = f;
            bp = make_pair(in, (in+1)%N);
        }

        push_relabel_max_flow(g, bp.first, bp.second); // prepare res map

        vector<int> s(N, false);
        queue<int> q;

        q.push(bp.first);
        s[bp.first] = true;
        vector<int> r;

        while(q.size()) {
            int u = q.front();
            q.pop();

            r.push_back(u);

            graph_traits<Graph>::out_edge_iterator ie, ie_end;
            for(tie(ie, ie_end) = out_edges(u, g); ie != ie_end; ++ie) {
                int v = target(*ie, g);
                if(s[v] || mr[*ie] == 0) continue;
                s[v] = true;
                q.push(v);
            }
        }

        cout << bf << endl << r.size() << " ";
        for(int er : r) cout << er << " ";
        cout << endl;
    }

    return 0;
}
