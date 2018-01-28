#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Segment_2<K>                                        S2;
typedef Delaunay_triangulation_2<K>                         DT;
typedef __uint128_t                                         bint;

pair<vector<bool>, int> covered(vector<vector<pair<int, bint> > > &n, bint p, vector<pair<int, bint> > &s, vector<pair<int, bint> > &e) {
    vector<int> v(n.size(), 0);
    int c; // current comp

    for(int iv = 0; iv < (int) v.size(); ++iv) {
        if(v[iv]) continue;
        c = iv+1;

        queue<int> q;
        q.push(iv);
        v[iv] = c;

        while(q.size()) {
            int top = q.front(); q.pop();

            for(auto en : n[top]) {
                if(v[en.first] || en.second > p) continue;
                q.push(en.first);
                v[en.first] = c;
            }
        }
    }

    int count = 0;
    vector<bool> g(s.size(), false);

    for(int im = 0; im < (int) s.size(); ++im) {
        g[im] = 4*s[im].second <= p && 4*e[im].second <= p && v[s[im].first] == v[e[im].first];
        if(g[im]) ++count;
    }

    return make_pair(g, count);
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M; long long W; bint P;
        cin >> N >> M >> W;
        P = W;

        map<P2, int> j;
        vector<P2> p(N);

        for(int in = 0; in < N; ++in) {
            int xj, yj;
            cin >> xj >> yj;
            p[in] = P2(xj, yj);

            j.emplace(p[in], in);
        }

        DT t;
        t.insert(p.begin(), p.end());

        vector<pair<int, bint> > s(M);
        vector<pair<int, bint> > e(M);

        for(int im = 0; im < M; ++im) {
            int xs, ys, xe, ye;
            cin >> xs >> ys >> xe >> ye;

            P2 ps = t.nearest_vertex(P2(xs, ys))->point();
            P2 pe = t.nearest_vertex(P2(xe, ye))->point();

            s[im] = make_pair(j[ps], squared_distance(ps, P2(xs, ys)));
            e[im] = make_pair(j[pe], squared_distance(pe, P2(xe, ye)));
        }

        vector<vector<pair<int, bint> > > n(N); // neighbors

        for(auto it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it) {
            S2 seg = t.segment(it);
            P2 v1 = seg.source();
            P2 v2 = seg.target();
            bint d = squared_distance(v1, v2);

            n[j[v1]].emplace_back(j[v2], d);
            n[j[v2]].emplace_back(j[v1], d);
        }

        pair<vector<bool>, int> res1 = covered(n, P, s, e), res2;

        for(bool eres1 : res1.first) cout << (eres1 ? "y" : "n");
        cout << endl;

        bint l = 0, r = ((bint) 1 << 53)*((bint) 1 << 53);

        while(l != r) {
            bint m = (l+r)/2;
            res2 = covered(n, m, s, e);
            if(res2.second < M) {
                l = m+1;
            } else {
                r = m;
            }
        }

        cout << (long long) l << endl;

        l = 0, r = P;

        while(l != r) {
            bint m = (l+r)/2;
            res2 = covered(n, m, s, e);
            bool more = res2.second < res1.second;
            if(!more) {
                int im;
                for(im = 0; im < M; ++im) {
                    if(res1.first[im] && !res2.first[im]) break;
                }
                more = im < M;
            }
            if(more) {
                l = m+1;
            } else {
                r = m;
            }
        }

        cout << (long long) l << endl;

    }

    return 0;
}
