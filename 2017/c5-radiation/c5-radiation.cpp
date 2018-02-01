#include<bits/stdc++.h>
#include<CGAL/Gmpzf.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>

using namespace std;
using namespace CGAL;

typedef Gmpzf                                   ET;
typedef Quadratic_program<ET>                   QP;
typedef Quadratic_program_solution<ET>          QPS;

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    
    while(T--) {
        
        int H, C, N;
        cin >> H >> C;
        
        N = H+C;
        vector<array<ET, 31> > x(N), y(N), z(N);
        
        for(int in = 0; in < N; ++in) {
            cin >> x[in][1] >> y[in][1] >> z[in][1];
            
            x[in][0] = 1;
            y[in][0] = 1;
            z[in][0] = 1;
            
            for(int id = 2; id < 31; ++id) {
                x[in][id] = x[in][id-1]*x[in][1];
                y[in][id] = y[in][id-1]*y[in][1];
                z[in][id] = z[in][id-1]*z[in][1];
            }
        }
        
        if(!H || !C) {
            cout << 0 << endl;
            continue;
        }
        
        int a = 0, b = 1;
        bool f = false;
        
        Quadratic_program_options o;
        o.set_pricing_strategy(QP_BLAND);
        
        while(a != b) {
            int D = std::min((a+b)/2, 30);
            
            QP lp(EQUAL, false, 0, false, 0);
            
            for(int in = 0; in < N; ++in) {
            
                int v = 0; // variable counter
            
                if(in < H) {
                    lp.set_r(in, SMALLER);
                    lp.set_b(in, -1);
                } else {
                    lp.set_r(in, LARGER);
                    lp.set_b(in, 1);
                }
                
                for(int dx = 0; dx <= D; ++dx) {
                    for(int dy = 0; dy <= D-dx; ++dy) {
                        for(int dz = 0; dz <= D-dx-dy; ++dz) {
                            ET p = x[in][dx]*y[in][dy]*z[in][dz];
                            lp.set_a(v, in, p);
                            v++;
                        }
                    }
                }
            }
            
            QPS lps = solve_linear_program(lp, ET(), o);
            
            if(lps.is_infeasible()) {
                if(!f) {
                    if(b < 30) b *= 2;
                    else break;
                } else {
                    a = D+1;
                }
                
            } else {
                f = true;
                b = D;
            }
        }
        
        if(!f) cout << "Impossible!" << endl;
        else   cout << a << endl;
    }
    
    return 0;
}

