#include<iostream>

#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpq.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Gmpq ET;
typedef Quadratic_program<ET> LP;
typedef Quadratic_program_solution<ET> PS;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> DT;
typedef Point_2<K> P2;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int A, S, B, E;
        cin >> A >> S >> B >> E;

        vector<P2> a, s, b;
        vector<int> da;

        for(int ia = 0; ia < A; ++ia) {
            int x, y, d; cin >> x >> y >> d;
            a.push_back(P2(x, y));
            da.push_back(d);
        }

        for(int is = 0; is < S; ++is) {
            int x, y; cin >> x >> y;
            s.push_back(P2(x, y));
        }

        for(int ib = 0; ib < B; ++ib) {
            int x, y; cin >> x >> y;
            b.push_back(P2(x, y));
        }

        DT d;
        d.insert(b.begin(), b.end());

        LP lp(LARGER, true, 0, true, E);

        for(int is = 0; is < S; ++is) {
            lp.set_c(is, 1);

            ET r;
            if(B) r = squared_distance(s[is], d.nearest_vertex(s[is])->point());

            for(int ia = 0; ia < A; ++ia) {
                ET c = squared_distance(s[is], a[ia]);

                lp.set_b(ia, da[ia]);

                if(B && r <= c) {
                    lp.set_a(is, ia, 0);
                    continue;
                }

                lp.set_a(is, ia, c > 1 ? 1/c : 1);
            }
        }

        PS ls = solve_linear_program(lp, ET());

        if(ls.is_infeasible() || ls.objective_value() > E) {
            cout << "n" << endl;
        } else {
            cout << "y" << endl;
        }
    }

    return 0;
}
