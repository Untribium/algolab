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
        map<P2, int> m; // mapping clients -> index

        for(int is = 0; is < (int) s.size(); ++is) {
            int rx, ry;
            cin >> rx >> ry;
            m.emplace(s[is] = P2(rx, ry), is);
        }

        DT t;
        t.insert(s.begin(), s.end());

        vector<vector<pair<int, K::FT> > > n(N);

        for(auto ie = t.finite_edges_begin(); ie != t.finite_edges_end(); ++ie) {
            P2 v1 = t.segment(ie).source();
            P2 v2 = t.segment(ie).target();
            K::FT d = squared_distance(v1, v2);
            n[m[v1]].emplace_back(m[v2], d);
            n[m[v2]].emplace_back(m[v1], d);
        }

        vector<int> k(N, 0); // component (and visited)
        vector<int> c(N, 0); // color

        for(int in = 0; in < (int) c.size(); ++in) {
            if(k[in]) continue;

            queue<int> q;
            q.push(in);
            k[in] = in+1; // 0 means not visited
            c[in] = 0;

            while(q.size()) {
                int top = q.front();
                q.pop();

                for(auto &en : n[top]) {
                    if(k[en.first] || en.second > R) continue;
                    k[en.first] = in+1;
                    c[en.first] = 1-c[top];
                    q.push(en.first);
                }
            }
        }

        vector<P2> p0, p1;
        for(int ic = 0; ic < (int) c.size(); ++ic) {
            if(c[ic]) p1.push_back(s[ic]);
            else p0.push_back(s[ic]);
        }

        DT t0, t1;
        t0.insert(p0.begin(), p0.end());
        t1.insert(p1.begin(), p1.end());

        bool f = true;

        for(auto ie = t0.finite_edges_begin(); ie != t0.finite_edges_end(); ++ie) {
            if(t0.segment(ie).squared_length() <= R) {
                f = false; break;
            }
        }

        for(auto ie = t1.finite_edges_begin(); f && ie != t1.finite_edges_end(); ++ie) {
            if(t1.segment(ie).squared_length() <= R) {
                f = false; break;
            }
        }

        for(int im = 0; im < M; ++im) {
            int xa, ya, xb, yb;
            cin >> xa >> ya >> xb >> yb;

            if(!f) {
                cout << "n"; continue;
            }

            P2 a = P2(xa, ya), b = P2(xb, yb);

            if(squared_distance(a, b) <= R) {
                cout << "y"; continue;
            }

            P2 u = t.nearest_vertex(a)->point();
            P2 v = t.nearest_vertex(b)->point();

            if(squared_distance(a, u) > R || squared_distance(b, v) > R) {
                cout << "n"; continue;
            }

            cout << (k[m[u]] == k[m[v]] ? "y" : "n");
        }

        cout << endl;
    }

    return 0;
}
