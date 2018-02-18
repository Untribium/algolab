#include<bits/stdc++.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpq.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Gmpq                                            ET;
typedef Quadratic_program<ET>                           QP;
typedef Quadratic_program_solution<ET>                  QPS;
typedef Exact_predicates_inexact_constructions_kernel   K;
typedef Point_2<K>                                      P2;

double ceil_to_double(const Quotient<ET> &e) {
    double d = std::ceil(to_double(e));
    while(d   <  e) d++;
    while(d-1 >= e) d--;
    return d;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int W, S, C, L, co = 0;
        cin >> W >> S >> C;

        vector<int> a(W), r(W*S);
        vector<P2> p(L = W+S);
        vector<vector<pair<int, int> > > o(L);

        QP lp(SMALLER, true, 0, false, 0);

        for(int iw = 0, sw; iw < W; ++iw) {
            cin >> p[iw] >> sw >> a[iw];
            lp.set_b(iw, sw);                        // supply
        }

        for(int is = 0, d, u; is < S; ++is) {
            cin >> p[W+is] >> d >> u;
            lp.set_b(W+S+is, 100*u);                 // alcohol
            lp.set_b(W+is,   d);                     // demand
            lp.set_r(W+is,   EQUAL);
        }

        for(int iw = 0; iw < W; ++iw) {
            for(int is = 0; is < S; ++is) {
                cin >> r[iw*S+is];
                r[iw*S+is] *= 100;                   // revenue
                lp.set_a(iw*S+is, iw,     1);        // supply
                lp.set_a(iw*S+is, W+is,   1);        // demand
                lp.set_a(iw*S+is, W+S+is, a[iw]);    // alcohol
            }
        }

        for(int ic = 0; ic < C; ++ic) {
            int xc, yc; K::FT rc;
            cin >> xc >> yc >> rc;

            for(int il = 0, in = 1; il < L; ++il) {
                if(squared_distance(P2(xc, yc), p[il]) < rc*rc) {
                    co += in; in = 0;
                    o[il].emplace_back(-rc, co);
                }
            }
        }

        for(int il = 0; C && il < L; ++il) {
            sort(o[il].begin(), o[il].end());
        }

        for(int iw = 0; iw < W; ++iw) {
            for(int is = 0, ps, pw; is < S; ++is, ps = 0, pw = 0) {
                while(C && ps < o[W+is].size() && pw < o[iw].size() && o[W+is][ps] == o[iw][pw] && ++ps && ++pw);
                if(C) r[iw*S+is] -= (o[W+is].size() - ps) + (o[iw].size() - pw);

                lp.set_c(iw*S+is, -r[iw*S+is]);
            }
        }

        QPS lps = solve_linear_program(lp, ET());

        if(lps.is_infeasible()) {
            cout << "RIOT!" << endl;
        } else {
            cout << (long long) -ceil_to_double(lps.objective_value()/100) << endl;
        }
    }

    return 0;
}
