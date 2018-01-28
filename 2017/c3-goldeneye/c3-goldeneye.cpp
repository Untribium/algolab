#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Delaunay_triangulation_2<K>                         DT;

int covered(vector<vector<pair<int, long long> > > &n, long long p, vector<pair<int, long long> > &s, vector<pair<int, long long> > &e, bool print) {
    vector<int> v(n.size(), 0); // component map

    for(int iv = 0; iv < (int) v.size(); ++iv) {
        if(v[iv]) continue;

        queue<int> q;
        q.push(iv);
        v[iv] = iv+1; // +1, so 0 means 'not visited'

        while(q.size()) {
            int top = q.front(); q.pop();

            for(auto en : n[top]) {
                if(v[en.first] || en.second > p) continue;
                q.push(en.first);
                v[en.first] = iv+1;
            }
        }
    }

    int count = 0; bool b;

    for(int im = 0; im < (int) s.size(); ++im) {
        b = 4*s[im].second <= p && 4*e[im].second <= p && v[s[im].first] == v[e[im].first];
        if(b) ++count;
        if(print) cout << (b ? "y" : "n");
    }

    return count;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M; long long P;
        cin >> N >> M >> P;

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

        vector<pair<int, long long> > s(M), e(M);

        for(int im = 0; im < M; ++im) {
            int xs, ys, xe, ye;
            cin >> xs >> ys >> xe >> ye;

            P2 ps = t.nearest_vertex(P2(xs, ys))->point();
            P2 pe = t.nearest_vertex(P2(xe, ye))->point();

            s[im] = make_pair(j[ps], squared_distance(ps, P2(xs, ys)));
            e[im] = make_pair(j[pe], squared_distance(pe, P2(xe, ye)));
        }

        vector<vector<pair<int, long long> > > n(N);    // neighbors

        for(auto it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it) {
            P2 v1 = t.segment(it).source();
            P2 v2 = t.segment(it).target();
            long long d = squared_distance(v1, v2);

            n[j[v1]].emplace_back(j[v2], d);
            n[j[v2]].emplace_back(j[v1], d);
        }

        int c = covered(n, P, s, e, true);              // subtask #1

        long long l = 0, r = LLONG_MAX;

        while(l != r) {                                 // subtask #2
            long long m = (l+r)/2;
            if(covered(n, m, s, e, false) < M) {
                l = m+1;
            } else {
                r = m;
            }
        }
        cout << endl << l << endl;

        l = 0, r = P;

        while(l != r) {                                 // subtask #3
            long long m = (l+r)/2;
            if(covered(n, m, s, e, false) < c) {
                l = m+1;
            } else {
                r = m;
            }
        }
        cout << l << endl;
    }

    return 0;
}
