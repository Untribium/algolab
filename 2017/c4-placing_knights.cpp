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
typedef property_map<Graph, edge_reverse_t>::type               ReverseMap;
typedef property_map<Graph, edge_residual_capacity_t>::type     ResidualMap;

void flow_edge(int u, int v, bool i, CapacityMap &mc, ReverseMap &mi, Graph &g) {
    Edge e, r;

    if(i) swap(u, v);

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    mc[e] = 1; mc[r] = 0;
    mi[e] = r; mi[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<vector<int> > u(N, vector<int>(N)); // usable
        Graph g(N*N+2);

        CapacityMap mc = get(edge_capacity, g);
        ReverseMap mi = get(edge_reverse, g);
        ResidualMap mr = get(edge_residual_capacity, g);

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                cin >> u[i][j];

                if(u[i][j] == 0) continue;

                int c = i*N+j, b = (i+j)%2;

                flow_edge(N*N+b, c, b, mc, mi, g);
                if(i > 0 && j > 1   && u[i-1][j-2]) flow_edge(c, (i-1)*N+(j-2), b, mc, mi, g);
                if(i > 0 && j < N-2 && u[i-1][j+2]) flow_edge(c, (i-1)*N+(j+2), b, mc, mi, g);
                if(i > 1 && j > 0   && u[i-2][j-1]) flow_edge(c, (i-2)*N+(j-1), b, mc, mi, g);
                if(i > 1 && j < N-1 && u[i-2][j+1]) flow_edge(c, (i-2)*N+(j+1), b, mc, mi, g);
            }
        }

        push_relabel_max_flow(g, N*N, N*N+1);

        boost::queue<int> q;
        vector<bool> v(N*N+2, false);
        v[N*N] = true;
        q.push(N*N);

        while(q.size()) {
            int top = q.top(); q.pop();

            graph_traits<Graph>::out_edge_iterator ie, ie_end;
            for(tie(ie, ie_end) = out_edges(top, g); ie != ie_end; ++ie) {
                int t = target(*ie, g);
                if(v[t] || mr[*ie] == 0) continue;
                q.push(t);
                v[t] = true;
            }
        }

        int count = 0;

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(u[i][j] && ((i+j)%2 ^ v[i*N+j])) count++;
            }
        }

        cout << count << endl;
    }

    return 0;
}
