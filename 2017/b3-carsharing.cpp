#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include<boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>        Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int,
    property<edge_reverse_t, Traits::edge_descriptor,
    property<edge_residual_capacity_t, int,
    property<edge_capacity_t, int> > > > >                  Graph;

typedef graph_traits<Graph>::edge_descriptor                Edge;
typedef property_map<Graph, edge_weight_t>::type            WeightMap;
typedef property_map<Graph, edge_capacity_t>::type          CapacityMap;
typedef property_map<Graph, edge_reverse_t>::type           ReverseMap;

void flow_edge(int u, int v, int c, int w, WeightMap &wm, CapacityMap &cm, ReverseMap &rm, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    wm[e] = w; wm[r] = -w;
    cm[e] = c; cm[r] = 0;
    rm[e] = r; rm[r] = e;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, S, P = 100, A = 100000, L = 0;
        cin >> N >> S;

        int c = 2;
        Graph g(c);

        WeightMap wm = get(edge_weight, g);
        CapacityMap cm = get(edge_capacity, g);
        ReverseMap rm = get(edge_reverse, g);

        vector<map<int, int> > v(S);

        for(int is = 0; is < S; ++is) {
            int rl;
            cin >> rl;

            L += rl;

            flow_edge(0, c, rl, 0, wm, cm, rm, g);
            v[is].emplace(0, c++);

            flow_edge(c, 1, INT_MAX, 0, wm, cm, rm, g);
            v[is].emplace(A, c++);
        }

        for(int in = 0; in < N; ++in) {
            int rs, rt, rd, ra, rp;
            cin >> rs >> rt >> rd >> ra >> rp;
            --rs; --rt;

            if(v[rs].find(rd) == v[rs].end()) {
                v[rs].emplace(rd, c++);
            }

            if(v[rt].find(ra) == v[rt].end()) {
                v[rt].emplace(ra, c++);
            }

            flow_edge(v[rs][rd], v[rt][ra], 1, (ra-rd)*P-rp, wm, cm, rm, g);
        }

        for(int iv = 0; iv < (int) v.size(); ++iv) {
            for(auto iev = v[iv].begin(); iev != --v[iv].end(); /* ++ in loop */) {
                pair<int, int> p = *iev, c = *(++iev); // previous, current
                flow_edge(p.second, c.second, INT_MAX, P*(c.first-p.first), wm, cm, rm, g);
            }
        }

        successive_shortest_path_nonnegative_weights(g, 0, 1);

        cout << L*A*P-find_flow_cost(g) << endl;
    }

    return 0;
}
