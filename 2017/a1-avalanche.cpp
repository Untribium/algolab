#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/max_cardinality_matching.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_weight_t, int> >                  Graph;
typedef adjacency_list<vecS, vecS, undirectedS>     UGraph;

typedef graph_traits<Graph>::edge_descriptor        Edge;
typedef graph_traits<Graph>::vertex_descriptor      Vertex;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, A, S, C, D;
        cin >> N >> M >> A >> S >> C >> D;

        Graph g1(N+(C-1)*S);
        property_map<Graph, edge_weight_t>::type wm = get(edge_weight, g1);
        Edge e;

        for(int im = 0; im < M; ++im) {
            char rw; int rx, ry, rz;
            cin >> rw >> rx >> ry >> rz;

            tie(e, ignore) = add_edge(rx, ry, g1);
            wm[e] = rz;

            if(rw == 'S') continue;

            tie(e, ignore) = add_edge(ry, rx, g1);
            wm[e] = rz;
        }

        vector<int> a(A), s(C*S);

        for(int &ea : a) cin >> ea;

        for(int is = 0; is < S; ++is) {
            cin >> s[is];

            if(C == 1) continue;

            s[S+is] = N+is;

            tie(e, ignore) = add_edge(s[is], N+is, g1);
            wm[e] = D;
        }

        vector<vector<int> > d(A, vector<int>(C*S));

        for(int ia = 0; ia < A; ++ia) {
            vector<int> td(N+(C-1)*S);
            dijkstra_shortest_paths(g1, a[ia],
                distance_map(make_iterator_property_map(td.begin(), get(vertex_index, g1))));
            for(int is = 0; is < (int) s.size(); ++is) d[ia][is] = td[s[is]];
        }

        int l = 0, r = 100000000;

        while(l != r) {
            UGraph g2(A+C*S);

            int m = (l+r)/2;

            for(int id = 0; id < (int) d.size(); ++id) {
                for(int jd = 0; jd < (int) d[id].size(); ++jd) {
                    if(d[id][jd] > m) continue;
                    add_edge(id, A+jd, g2);
                }
            }

            vector<int> mate(A+C*S);

            edmonds_maximum_cardinality_matching(g2, make_iterator_property_map(mate.begin(), get(vertex_index, g2)));

            if((int) matching_size(g2, &mate[0]) == A) {
                r = m;
            } else {
                l = m+1;
            }
        }

        cout << (l + D) << endl;
    }

    return 0;
}
