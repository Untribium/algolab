#include<stdio.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

int main() {
    while(true) {
        int n;
        scanf("%d", &n);

        if(!n) {
            return 0;
        }

        long x, y, a, b;
        scanf("%ld %ld %ld %ld", &x, &y, &a, &b);

        K::Point_2 p(x, y), q(a, b);

        K::Ray_2 r(p, q);

        bool hit = false;

        for(int i = 0; i < n; ++i) {
            scanf("%ld %ld %ld %ld", &x, &y, &a, &b);

            if(!hit) {
                K::Point_2 u(x, y), v(a, b);
                hit |= CGAL::do_intersect(r, K::Segment_2(u, v));
            }
        }

        if(hit) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }

    }
}
