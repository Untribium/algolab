#include<iostream>
#include<map>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpzf.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel   K;
typedef Point_2<K>                                      P2;
typedef Delaunay_triangulation_2<K>                     DT;
typedef Quadratic_program<double>                       QP;
typedef Quadratic_program_solution<double>              QPS;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int Z, U, V, W, A, G;
        cin >> Z >> U >> V >> W >> A >> G;

        vector<P2> p(G); // position
        map<P2, int> i; // point to ig
        vector<tuple<int, int, int> > l(G); // leak
        map<P2, int> z; // wage/h

        for(int ig = 0; ig < G; ++ig) {
            cin >> p[ig] >> get<0>(l[ig]) >> get<1>(l[ig]) >> get<2>(l[ig]);
            i[p[ig]] = ig;
        }

        DT t;
        t.insert(p.begin(), p.end());

        for(int ia = 0; ia < A; ++ia) {
            P2 pa;
            int za;
            cin >> pa >> za;

            P2 n = t.nearest_vertex(pa)->point();

            if(z.find(n) == z.end()) {
                z.emplace(n, za);
            } else {
                z[n] = std::min(z[n], za);
            }
        }

        QP lp(LARGER, true, 0, true, 24);

        int n = 0;
        for(auto ez : z) {

            lp.set_a(n, 0, get<0>(l[i[ez.first]]));
            lp.set_a(n, 1, get<1>(l[i[ez.first]]));
            lp.set_a(n, 2, get<2>(l[i[ez.first]]));

            lp.set_c(n++,  ez.second);
        }

        lp.set_b(0, U);
        lp.set_b(1, V);
        lp.set_b(2, W);

        QPS lps = solve_linear_program(lp, double());

        if(lps.is_infeasible() || lps.objective_value() > Z) {
            cout << "H" << endl;
        } else {
            cout << "L" << endl;
        }
    }
}
