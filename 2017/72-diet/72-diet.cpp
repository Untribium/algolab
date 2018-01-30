#include<bits/stdc++.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpq.h>

using namespace std;
using namespace CGAL;

typedef Gmpq                                ET;
typedef Quadratic_program<ET>               QP;
typedef Quadratic_program_solution<ET>      QPS;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {
        int N, M;
        cin >> N >> M;

        if(!N) return 0;

        QP lp(EQUAL, true, 0, false, 0);

        for(int in = 0; in < N; ++in) {
            int rl, rh; // low, high
            cin >> rl >> rh;

            lp.set_b(in,   rl);
            lp.set_r(in,   LARGER);

            lp.set_b(N+in, rh);
            lp.set_r(N+in, SMALLER);
        }

        for(int im = 0; im < M; ++im) {
            int rp;
            cin >> rp;

            lp.set_c(im, rp);

            for(int in = 0; in < N; ++in) {
                int rc;
                cin >> rc;

                lp.set_a(im, in,   rc);
                lp.set_a(im, N+in, rc);
            }
        }

        QPS lps = solve_nonnegative_linear_program(lp, ET());

        if(lps.is_infeasible()) {
            cout << "No such diet." << endl;
        } else {
            double d = to_double(lps.objective_value());
            cout << (long long) std::floor(d) << endl;
        }
    }
}
