#include<iostream>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef CGAL::Gmpz ET;

typedef Quadratic_program<int> QP;
typedef Quadratic_program_solution<ET> QS;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {

        int N, D;
        cin >> N;

        if(!N) break;

        cin >> D;

        QP p(CGAL::SMALLER, false, 0, false, 0);

        for(int in = 0; in < N; ++in) {
            int a = 0;
            for(int id = 0; id < D; ++id) {
                int v;
                cin >> v;
                p.set_a(id, in, v);
                a += v*v;
            }

            p.set_a(D, in, std::sqrt(a));

            int b;
            cin >> b;

            p.set_b(in, b);
        }

        for(int id = 0; id < D; ++id) {
            p.set_c(id, 0);
        }

        p.set_c(D, -1);
        p.set_l(D, true, 0);

        QS s = solve_linear_program(p, ET());

        if(s.is_infeasible()) {
            cout << "none" << endl;
        } else if(s.is_unbounded()) {
            cout << "inf" << endl;
        } else {
            ET r = -s.objective_value().numerator()/s.objective_value().denominator();
            cout << r << endl;
        }
    }

    return 0;
}
