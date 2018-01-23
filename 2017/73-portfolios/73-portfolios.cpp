#include<iostream>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpq.h>

using namespace std;
using namespace CGAL;

typedef Gmpq ET;
typedef Quadratic_program<ET> QP;
typedef Quadratic_program_solution<ET> QPS;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {

        int N, M;
        cin >> N >> M;

        if(!N) return 0;

        QP p(SMALLER, true, 0, false, 0);

        p.set_r(0, SMALLER);
        p.set_r(1, LARGER);

        for(int in = 0; in < N; ++in) {
            int c, r;
            cin >> c >> r;

            p.set_a(in, 0, c);
            p.set_a(in, 1, r);
        }

        for(int in = 0; in < N; ++in) {
            for(int jn = 0; jn < N; ++jn) {
                int v;
                cin >> v;

                p.set_d(in, jn, 2*v);
            }
        }

        for(int im = 0; im < M; ++im) {

            int C, R, V;
            cin >> C >> R >> V;

            p.set_b(0, C);
            p.set_b(1, R);

            QPS s = solve_nonnegative_quadratic_program(p, ET());

            if(s.is_infeasible() || s.is_unbounded() || s.objective_value() > ET(V)) {
                cout << "No." << endl;
            } else {
                cout << "Yes." << endl;
            }
        }
    }
}
