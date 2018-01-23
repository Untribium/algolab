#include<iostream>

#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Gmpz ET;
typedef Quadratic_program<int> QP;
typedef Quadratic_program_solution<ET> QS;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    QP p1(SMALLER, false, 0, false, 0);

    p1.set_c(1,     0);                                                                 // set in case
    p1.set_d(0, 0,  0);                                                                 // set in case

    p1.set_l(0, true, 0); p1.set_l(1, true, 0);                                         // x,y >= 0

    p1.set_a(0, 0,  1);   p1.set_a(1, 0,  1);   p1.set_b(   0,  4);                     // x + y <= 4

    p1.set_a(0, 1,  4);   p1.set_a(1, 1,  2);   p1.set_b(   1,  0);                     // 4x + 2y <= ab, ab set in case

    p1.set_a(0, 2, -1);   p1.set_a(1, 2,  1);   p1.set_b(   2,  1);                     // -x + y <= 1

    QP p2(LARGER, false, 0, false, 0);

    p2.set_c(1,     0);                                                                 // set in case
    p2.set_d(0, 0,  0);                         p2.set_d(2, 2,  2);                     // 0,0 set in case

    p2.set_u(0, true, 0); p2.set_u(1, true, 0);                                         // x,y <= 0

    p2.set_a(0, 0,  1);   p2.set_a(1, 0,  1);                       p2.set_b(   0, -4); // x + y >= -4

    p2.set_a(0, 1,  4);   p2.set_a(1, 1,  2);   p2.set_a(2, 1,  1); p2.set_b(   1,  0); // 4x + 2y + z^2 >= -ab, -ab set in case

    p2.set_a(0, 2, -1);   p2.set_a(1, 2,  1);   p2.set_b(   2, -1);                     // -x + y >= -1

    while(true) {

        int P, A, B;
        cin >> P;

        if(!P) break;

        cin >> A >> B;

        if(P == 1) {
            p1.set_d(0, 0, 2*A);
            p1.set_c(1,   -B);

            p1.set_b(   1, A*B);

            QS s = solve_quadratic_program(p1, ET());

            if(s.is_infeasible()) {
                cout << "no" << endl;
            } else if(s.is_unbounded()) {
                cout << "unbounded" << endl;
            } else {
                // integer division (Gmpz)
                ET r = -s.objective_value().numerator()/s.objective_value().denominator();
                long long ll = floor(r.to_double());
                cout << ll << endl;
            }

        } else {
            p2.set_d(0, 0,  2*A);
            p2.set_c(1,     B);

            p2.set_b(   1, -A*B);

            QS s = solve_quadratic_program(p2, ET());

            if(s.is_infeasible()) {
                cout << "no" << endl;
            } else if(s.is_unbounded()) {
                cout << "unbounded" << endl;
            } else {
                // integer division (Gmpz)
                ET r = s.objective_value().numerator()/s.objective_value().denominator();
                long long ll = ceil(r.to_double());
                cout << ll << endl;
            }
        }

    }
}
