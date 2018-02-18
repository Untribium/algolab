#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel           K;
typedef Point_2<K>                                              P2;
typedef Delaunay_triangulation_2<K>                             DT;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M; K::FT R;
        cin >> N >> M >> R;
        R *= R;

        vector<P2> s(N); // clients
        map<P2, int> m;  // mapping clients -> index
        vector<vector<pair<int, K::FT> > > n(N);

        for(int is = 0, rx, ry; is < (int) s.size(); ++is) {
            cin >> rx >> ry;
            m.emplace(s[is] = P2(rx, ry), is);
        }

        DT t;
        t.insert(s.begin(), s.end());

        for(auto ie = t.finite_edges_begin(); ie != t.finite_edges_end(); ++ie) {
            P2 v1 = t.segment(ie).source();
            P2 v2 = t.segment(ie).target();
            n[m[v1]].emplace_back(m[v2], squared_distance(v1, v2));
            n[m[v2]].emplace_back(m[v1], squared_distance(v1, v2));
        }

        vector<int> c(N, 0); // component map (0 = not visited)
        vector<vector<P2> > p(2);

        for(int in = 0; in < (int) c.size(); ++in) {
            if(c[in]) continue;
            queue<pair<int, int> > q;
            q.emplace(in, 0);
            c[in] = in+1;

            while(q.size()) {
                pair<int, int> top = q.front(); q.pop();
                for(auto &en : n[top.first]) {
                    if(c[en.first] || en.second > R) continue;
                    c[en.first] = in+1;
                    p[1-top.second].push_back(s[en.first]);
                    q.emplace(en.first, 1-top.second);
                }
            }
        }

        bool f = true;

        for(int it = 0; it < 2; ++it) {
            DT tc;
            tc.insert(p[it].begin(), p[it].end());
            for(auto ie = tc.finite_edges_begin(); ie != tc.finite_edges_end(); ++ie) {
                if(tc.segment(ie).squared_length() <= R) {
                    f = false; break;
                }
            }
        }

        for(int im = 0, xa, ya, xb, yb; im < M; ++im) {
            cin >> xa >> ya >> xb >> yb;

            P2 a = P2(xa, ya), b = P2(xb, yb);

            if(!f || squared_distance(a, b) <= R) {
                cout << (!f ? "n" : "y"); continue;
            }

            P2 u = t.nearest_vertex(a)->point();
            P2 v = t.nearest_vertex(b)->point();

            if(squared_distance(a, u) > R || squared_distance(b, v) > R) {
                cout << "n"; continue;
            }

            cout << (c[m[u]] == c[m[v]] ? "y" : "n");
        }
        cout << endl;
    }

    return 0;
}
