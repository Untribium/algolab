#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Delaunay_triangulation_2<K>                         DT;

int T, P, L;
long long H;
vector<int> w; // winners

int survivors(int m, vector<pair<P2, long long> > &p, vector<P2> &l, bool f) {

    if(f) w.clear();

    DT t;
    t.insert(l.begin(), l.begin()+m);

    int c = 0;

    for(int ip = 0; ip < (int) p.size(); ++ip) {
        P2 n = t.nearest_vertex(p[ip].first)->point();
        long long d = squared_distance(n, p[ip].first);

        if(d >= p[ip].second*p[ip].second) { // alive
            c++;
            if(!f) break;
            w.push_back(ip);
        }
    }

    return c;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;

    while(T--) {

        cin >> P >> L;

        vector<pair<P2, long long> > p(P);
        vector<P2> l(L);

        for(auto &ep : p) {
            int x, y, r;
            cin >> x >> y >> r;

            ep = make_pair(P2(x, y), r);
        }

        cin >> H;

        for(auto &ep : p) ep.second += H;

        for(P2 &el : l) {
            int x, y;
            cin >> x >> y;

            el = P2(x, y);
        }

        int a = 0, b = L, m, s;

        while(a != b) {

            m = (a+b+1)/2;

            s = survivors(m, p, l, false);

            if(s > 0) {
                a = m;
            } else {
                b = m-1;
            }
        }

        survivors(a, p, l, true);

        for(int ew : w) cout << ew << " ";

        cout << endl;
    }
}
