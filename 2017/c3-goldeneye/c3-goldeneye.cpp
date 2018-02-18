#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Delaunay_triangulation_2<K>                         DT;

int covered(vector<vector<pair<int, long long> > > &n, vector<pair<int, long long> > &s, vector<pair<int, long long> > &e, long long p, bool print) {
    vector<int> v(n.size(), 0); // component map

    for(int iv = 0; iv < (int) v.size(); ++iv) {
        if(v[iv]) continue;
        queue<int> q;
        q.push(iv);
        v[iv] = iv+1; // +1, 0 = 'not visited'

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

long long bsearch(vector<vector<pair<int, long long> > > &n, vector<pair<int, long long> > &s, vector<pair<int, long long> > &e, long long l, long long r, int c) {
    while(l != r) {
        long long m = (l+r)/2;

        if(covered(n, s, e, m, false) < c) l = m+1;
        else r = m;
    }
    return l;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M; long long P;
        cin >> N >> M >> P;

        map<P2, int> j;                                 // jammer to index
        vector<P2> p(N);                                // jammer locations
        vector<pair<int, long long> > s(M), e(M);       // start and endpoints of missions
        vector<vector<pair<int, long long> > > n(N);    // neighbors

        for(int in = 0, xj, yj; in < N; ++in) {
            cin >> xj >> yj;
            p[in] = P2(xj, yj);
            j.emplace(p[in], in);
        }

        DT t;
        t.insert(p.begin(), p.end());

        for(auto it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it) {
            P2 v1 = t.segment(it).source();
            P2 v2 = t.segment(it).target();

            n[j[v1]].emplace_back(j[v2], squared_distance(v1, v2));
            n[j[v2]].emplace_back(j[v1], squared_distance(v1, v2));
        }

        for(int im = 0, xs, ys, xe, ye; im < M; ++im) {
            cin >> xs >> ys >> xe >> ye;
            P2 ps = t.nearest_vertex(P2(xs, ys))->point();
            P2 pe = t.nearest_vertex(P2(xe, ye))->point();

            s[im] = make_pair(j[ps], squared_distance(ps, P2(xs, ys)));
            e[im] = make_pair(j[pe], squared_distance(pe, P2(xe, ye)));
        }

        int c = covered(n, s, e, P, true);
        cout << endl << bsearch(n, s, e, 0, LLONG_MAX, M) << endl;
        cout <<         bsearch(n, s, e, 0, P, c) << endl;
    }

    return 0;
}
