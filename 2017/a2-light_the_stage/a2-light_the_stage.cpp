#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Delaunay_triangulation_2<K>                         DT;

long long T, P, L, H;
vector<int> w; // winners

bool survivors(int a, int m, vector<pair<P2, long long> > &p, vector<P2> &l) {

    DT t;
    t.insert(l.begin()+a, l.begin()+m);

    vector<int> g;

    for(int ip : w) {
        P2 n = t.nearest_vertex(p[ip].first)->point();
        K::FT d = squared_distance(n, p[ip].first);

        if(d >= p[ip].second*p[ip].second) { // alive
            g.push_back(ip);
        }
    }

    if(g.size()) {
        w = g;
    }

    return g.size() > 0;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;

    while(T--) {

        cin >> P >> L;

        vector<pair<P2, long long> > p(P);
        vector<P2> l(L);

        w.clear();

        for(int ip = 0; ip < (int) p.size(); ++ip) {
            long long x, y, r;
            cin >> x >> y >> r;

            p[ip] = make_pair(P2(x, y), r);
            w.push_back(ip);
        }

        cin >> H;

        for(auto &ep : p) ep.second += H;

        for(P2 &el : l) {
            long long x, y;
            cin >> x >> y;

            el = P2(x, y);
        }

        int a = 0, b = L, m, s;

        while(a != b) {

            m = (a+b)/2+1;

            if(survivors(a, m, p, l)) {
                a = m;
            } else {
                b = m-1;
            }
        }

        for(int ew : w) cout << ew << " ";

        cout << endl;
    }
}
