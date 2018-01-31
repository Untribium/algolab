#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel           K;
typedef Point_2<K>                                              P2;
typedef Delaunay_triangulation_2<K>                             DT;
typedef Gmpq                                                    ET;
typedef Quadratic_program<ET>                                   QP;
typedef Quadratic_program_solution<ET>                          QPS;

void read_point(P2 &p) {
    int rx, ry;
    cin >> rx >> ry;
    p = P2(rx, ry);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int S, P, H, I;
        cin >> S >> P >> H >> I;

        vector<P2> s(S), p(P), h(H); // position (sensors, MPEs, henchmen)
        vector<int> e(S); // energy (sensor)

        bool skip = false, feas = false;

        for(int is = 0; is < S; ++is) {
            read_point(s[is]);
            cin >> e[is];
            if(e[is] > I) skip = true;
        }

        for(int ip = 0; ip < P; ++ip) read_point(p[ip]);
        for(int ih = 0; ih < H; ++ih) read_point(h[ih]);

        DT t;
        if(H) t.insert(h.begin(), h.end());

        vector<vector<pair<int, K::FT> > > r(S); // MPEs in range

        for(int ip = 0; ip < P; ++ip) {
            K::FT l, d;
            if(H) l = squared_distance(t.nearest_vertex(p[ip])->point(), p[ip]);
            for(int is = 0; is < S; ++is) {
                d = squared_distance(p[ip], s[is]);
                if(!H || d < l) r[is].emplace_back(ip, d);
            }
        }

        int a = 0, b = 1;

        while(!skip && a != b) {
            int m = std::min((a+b)/2, P);

            QP lp(LARGER, true, 0, true, I);

            for(int is = 0; is < S; ++is) {
                lp.set_b(is, e[is]);
                for(auto er : r[is]) {
                    if(er.first >= m) break;
                    lp.set_a(er.first, is, K::FT(1)/er.second);
                }
            }

            for(int ip = 0; ip < m; ++ip) lp.set_c(ip, 1);

            QPS lps = solve_nonnegative_linear_program(lp, ET());

            if(lps.is_infeasible() || lps.objective_value() > ET(I)) {
                if(!feas) {
                    if(m < P) b *= 2;
                    else break;
                } else {
                    a = m+1;
                }
            } else {
                feas = true;
                b = m;
            }
        }

        if(!feas) cout << "impossible" << endl;
        else cout << a << endl;
    }

    return 0;
}
