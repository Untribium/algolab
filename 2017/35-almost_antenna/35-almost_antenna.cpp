#include<iostream>
#include<vector>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef Min_circle_2_traits_2<K>  Traits;
typedef Min_circle_2<Traits>      MC;
typedef Point_2<K>                P2;

double ceil_to_double(const K::FT& x) {
    double a = ceil(to_double(x));
    while(a < x) a += 1;
    while(a-1 >= x) a -= 1;
    return a;
}

int main() {

    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);

    while(true) {
        int N;
        cin >> N;

        if(!N) break;

        vector<P2> p(N);

        for(P2& ep : p) {
            long x, y;
            cin >> x >> y;
            ep = P2(x, y);
        }

        MC m(p.begin(), p.end(), true);

        K::FT r = m.circle().squared_radius();
        P2 c = m.circle().center();

        vector<P2> s;
        vector<P2> i;

        for(P2& ep : p) {
            if(squared_distance(c, ep) == r) {
                s.push_back(ep);

                if(s.size() > 3) break;

            } else {
                i.push_back(ep);
            }
        }

        int ns = s.size(), ni = i.size();

        if(ns == 2 || ns == 3) {
            for(int is = 0; is < ns; ++is) {

                i.resize(ni);

                for(int js = 0; js < ns; ++js) {
                    if(js != is) {
                        i.push_back(s[js]);
                    }
                }

                MC cs(i.begin(), i.end(), true);

                r = CGAL::min(r, cs.circle().squared_radius());
            }
        }

        cout << ceil_to_double(sqrt(r)) << endl;
    }
    return 0;
}
