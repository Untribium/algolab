#include<stdio.h>
#include<math.h>
#include<stdexcept>

#include<CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

double floor_to_double(const K::FT& x) {
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

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

        K::Point_2 c;
        K::FT d;
        bool hit = false;

        for(int i = 0; i < n; ++i) {
            scanf("%ld %ld %ld %ld", &x, &y, &a, &b);

            K::Segment_2 s(K::Point_2(x, y), K::Point_2(a, b));

            if(CGAL::do_intersect(r, s)) {
                auto o = CGAL::intersection(r, s);
                K::FT tmp_d;

                if(const K::Point_2* op = boost::get<K::Point_2>(&*o)) {
                    tmp_d = CGAL::squared_distance(p, *op);
                    if(!hit || tmp_d < d) {
                        c = *op;
                        d = tmp_d;
                    }
                }
                else if (const K::Segment_2* os = boost::get<K::Segment_2>(&*o)) {
                    tmp_d = CGAL::squared_distance(p, (*os)[0]);
                    if(!hit || tmp_d < d) {
                        c = (*os)[0];
                        d = tmp_d;
                    }

                    tmp_d = CGAL::squared_distance(p, (*os)[1]);
                    if(tmp_d < d) {
                        c = (*os)[1];
                        d = tmp_d;
                    }
                }
                else {
                    throw runtime_error("invalid intersect");
                }

                hit = true;
            }
        }

        if(hit) {
            printf("%.0lf %.0lf\n", floor_to_double(c.x()), floor_to_double(c.y()));
        }
        else {
            printf("no\n");
        }
    }

    return 0;
}
