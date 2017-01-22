#include<stdio.h>
#include<CGAL/basic.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpz.h>

#include<iostream>

using namespace std;
using namespace CGAL;

typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
    while(true) {
        int n;
        scanf("%i", &n);

        if(!n) {
            return 0;
        }

        int d;
        scanf("%i", &d);

        Program lp(CGAL::SMALLER, false, 0, false, 0);

        lp.set_c(d, -1);
        lp.set_l(d, true, 0);

        for(int in = 0; in < n; ++in) {
            int norm = 0;

            for(int id = 0; id < d; ++id) {
                int ai;
                scanf("%i", &ai);
                lp.set_a(id, in, ai);
                norm += ai*ai;
            }

            norm = std::sqrt(norm);
            lp.set_a(d, in, norm);

            int bi;
            scanf("%i", &bi);
            lp.set_b(in, bi);
        }

        Solution s = solve_linear_program(lp, ET());

        if(s.is_infeasible()) {
            printf("none\n");
        } else if(s.is_unbounded()) {
            printf("inf\n");
        } else {
            ET r = -s.objective_value().numerator()/s.objective_value().denominator();
            cout << r << endl;
        }
    }
}
