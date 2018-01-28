#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel           K;
typedef Exact_predicates_exact_constructions_kernel_with_sqrt   KQ;
typedef Point_2<K>                                              P2;
typedef Delaunay_triangulation_2<K>                             DT;

KQ::FT r2t(const K::FT &d) {
    KQ::FT f = d;
    return CGAL::sqrt((CGAL::sqrt(f)-1)/2);
}

double ceil_to_double(const KQ::FT &x) {
    double a = std::ceil(to_double(x));
    while(a < x) a++;
    while(a-1 >= x) a--;
    return a;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {

        int N;
        cin >> N;

        if(!N) return 0;

        K::FT L, B, R, T;
        cin >> L >> B >> R >> T;

        vector<P2> p(N);
        vector<K::FT> m(N); // min squared dist to death
        map<P2, int> j;

        for(int ip = 0; ip < N; ++ip) {
            K::FT rx, ry;
            cin >> rx >> ry;

            p[ip] = P2(rx, ry);

            m[ip] = (rx-L)*(rx-L);
            m[ip] = std::min(m[ip], (R-rx)*(R-rx));
            m[ip] = std::min(m[ip], (ry-B)*(ry-B));
            m[ip] = std::min(m[ip], (T-ry)*(T-ry));
            m[ip] *= 4;

            j.emplace(p[ip], ip);
        }

        DT t;
        t.insert(p.begin(), p.end());

        for(auto it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it) {
            P2 v1 = t.segment(it).source();
            P2 v2 = t.segment(it).target();
            K::FT d = squared_distance(v1, v2);
            m[j[v1]] = std::min(m[j[v1]], d);
            m[j[v2]] = std::min(m[j[v2]], d);
        }

        sort(m.begin(), m.end());

        // also works...
        // cout << (long long) std::ceil(std::sqrt((std::sqrt(m[0])-1)/2)) << " ";
        // cout << (long long) std::ceil(std::sqrt((std::sqrt(m[N/2])-1)/2)) << " ";
        // cout << (long long) std::ceil(std::sqrt((std::sqrt(m[N-1])-1)/2)) << endl;

        cout << (long long) ceil_to_double(r2t(m[0])) << " ";
        cout << (long long) ceil_to_double(r2t(m[N/2])) << " ";
        cout << (long long) ceil_to_double(r2t(m[N-1])) << endl;
    }
}
