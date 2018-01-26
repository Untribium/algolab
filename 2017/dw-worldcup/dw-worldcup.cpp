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

        int W, S, C;
        cin >> W >> S >> C;

        vector<int> a(W);
        vector<P2> pw(W), ps(S);

        vector<vector<pair<int, int> > > ow(W), os(S);

        vector<int> r(W*S);

        QP lp(SMALLER, true, 0, false, 0);

        for(int iw = 0; iw < W; ++iw) {
            int xw, yw, sw;
            cin >> xw >> yw >> sw >> a[iw];

            pw[iw] = P2(xw, yw);

            lp.set_b(iw, sw);                        // supply
        }

        for(int is = 0; is < S; ++is) {
            int xs, ys, d, u;
            cin >> xs >> ys >> d >> u;

            ps[is] = P2(xs, ys);

            lp.set_b(W+is,   d);                     // demand
            lp.set_r(W+is,   EQUAL);
            lp.set_b(W+S+is, 100*u);                 // alcohol
        }

        for(int iw = 0; iw < W; ++iw) {
            for(int is = 0; is < S; ++is) {
                int rev;
                cin >> rev;

                r[iw*S+is] = rev*100;                // revenue

                lp.set_a(iw*S+is, iw,     1);        // supply

                lp.set_a(iw*S+is, W+is,   1);        // demand
                lp.set_a(iw*S+is, W+S+is, a[iw]);    // alcohol
            }
        }

        int co = 0;

        for(int ic = 0; ic < C; ++ic) {
            int xc, yc;
            K::FT rc;
            cin >> xc >> yc >> rc;

            P2 cc(xc, yc);

            bool in = false;

            for(int iw = 0; iw < W; ++iw) {
                if(squared_distance(cc, pw[iw]) < rc*rc) {
                    in = true;
                    ow[iw].emplace_back(-rc, co);
                }
            }

            for(int is = 0; is < S; ++is) {
                if(squared_distance(cc, ps[is]) < rc*rc) {
                    in = true;
                    os[is].emplace_back(-rc, co);
                }
            }

            if(in) co++;
        }

        for(int iw = 0; iw < W && C; ++iw) {
            sort(ow[iw].begin(), ow[iw].end());
        }

        for(int is = 0; is < S && C; ++is) {
            sort(os[is].begin(), os[is].end());
        }

        for(int iw = 0; iw < W; ++iw) {
            for(int is = 0; is < S; ++is) {
                int rev = r[iw*S+is];
                if(C) {
                    int ps = 0, pw = 0;

                    while(ps < os[is].size() && pw < ow[iw].size() && os[is][ps] == ow[iw][pw]) {
                        ps++; pw++;
                    }

                    rev -= os[is].size() - ps;
                    rev -= ow[iw].size() - pw;
                }

                lp.set_c(iw*S+is, -rev);
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
