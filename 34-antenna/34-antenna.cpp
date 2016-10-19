#include<stdio.h>
#include<vector>

#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a-1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

int main() {
    while(true) {
        int n;
        scanf("%i", &n);

        if(!n) {
            return 0;
        }

        vector<K::Point_2> p;

        for(int i = 0; i < n; ++i) {
            long x, y;
            scanf("%ld %ld", &x, &y);

            p.push_back(K::Point_2(x, y));
        }

        Min_circle mc(&p[0], &p[n], true);

        printf("%.0lf\n", ceil_to_double(sqrt(mc.circle().squared_radius())));
    }
}
