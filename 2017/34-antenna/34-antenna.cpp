#include<iostream>
#include<vector>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef Min_circle_2_traits_2<K>  Traits;
typedef Min_circle_2<Traits>      MC;
typedef Point_2<K>                P2;

double ceil_to_double(const K::FT& x) {
    double a = ceil(to_double(x));
    while(a < x)    a += 1;
    while(a-1 >= x) a -= 1;
    return a;
}

int main() {

    ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

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

        MC c(p.begin(), p.end(), true);

        cout << ceil_to_double(sqrt(c.circle().squared_radius())) << endl;
    }
}
