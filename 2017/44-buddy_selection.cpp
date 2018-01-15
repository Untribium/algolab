#include<iostream>
#include<vector>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

typedef graph_traits<Graph>::vertex_descriptor  Vertex;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        uint N, C, F;
        cin >> N >> C >> F;

        boost::unordered_map<string, vector<int> > m;
        vector<vector<uint> > p(N, vector<uint>(N));

        for(uint in = 0; in < N; ++in) {
            for(uint ic = 0; ic < C; ++ic) {
                string a;
                cin >> a;

                if(m.find(a) == m.end()) {
                    m.emplace(a, vector<int>(0));
                } else {
                    for(int ea : m[a]) {
                        p[ea][in]++;
                    }
                }

                m[a].push_back(in);
            }
        }

        Graph g(N);

        for(uint ip = 0; ip < N; ++ip) {
            for(uint jp = ip+1; jp < N; ++jp) {
                if(p[ip][jp] > F) {
                    add_edge(ip, jp, g);
                }
            }
        }

        vector<Vertex> x(N);

        while(!checked_edmonds_maximum_cardinality_matching(g,
            make_iterator_property_map(x.begin(), get(vertex_index, g)))) {}

        if(matching_size(g, make_iterator_property_map(x.begin(), get(vertex_index, g))) == N/2) {
            cout << "not optimal" << endl;
        } else {
            cout << "optimal" << endl;
        }
    }

    return 0;
}
