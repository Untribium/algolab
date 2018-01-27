#include<bits/stdc++.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Segment_2<K>                                        S2;
typedef Delaunay_triangulation_2<K>                         DT;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        long long R;
        cin >> N >> R;

        R *= R;

        vector<P2> p(N);
        map<P2, int> m;

        for(int ip = 0; ip < N; ++ip) {
            int rx, ry;
            cin >> rx >> ry;

            p[ip] = P2(rx, ry);
            m.emplace(p[ip], ip);
        }

        int l = 1, r = N/2; // empire+rebels < N

        while(l != r) {
            int k = (l+r+1)/2;

            DT t;
            t.insert(p.begin()+k, p.end());

            vector<vector<int> > d(N);

            for(auto ie = t.finite_edges_begin(); ie != t.finite_edges_end(); ie++) {
                S2 s = t.segment(ie);

                if(s.squared_length() > R) continue;

                int a = m[s.source()], b = m[s.target()];

                d[a].push_back(b);
                d[b].push_back(a);
            }

            vector<bool> v(N, false);
            int c;

            for(int iv = k; iv <= N-k; ++iv) {
                if(v[iv]) continue;

                queue<int> q;
                q.push(iv);
                v[iv] = true;
                c = 1;

                while(q.size() && c < k) {
                    int top = q.front();
                    q.pop();

                    for(int eed : d[top]) {
                        if(eed <= k || v[eed]) continue;
                        q.push(eed);
                        c++;
                        v[eed] = true;
                    }
                }

                if(c >= k) break;
            }

            if(c < k) {
                r = k-1;
            } else {
                l = k;
            }
        }

        cout << l << endl;
    }

    return 0;
}
