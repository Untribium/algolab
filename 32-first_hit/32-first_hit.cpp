#include<stdio.h>
#include<math.h>
#include<stdexcept>

#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

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

        IK::Point_2 ip(x, y), iq(a, b);
        IK::Ray_2 ir(ip, iq);
        IK::Direction_2 iw(ir);

        K::Point_2 c;
        K::FT d;
        bool hit = false;

        for(int i = 0; i < n; ++i) {
            scanf("%ld %ld %ld %ld", &x, &y, &a, &b);

            IK::Segment_2 is(IK::Point_2(x, y), IK::Point_2(a, b));

            if(CGAL::do_intersect(ir, is)) {
                K::Point_2 p1(x, y);
                K::Point_2 p2(a, b);

                K::FT tmp_d;

                IK::Direction_2 ws(is);
                if(ws == iw || ws == -iw) {
                    tmp_d = CGAL::squared_distance(p, p1);
                    if(!hit || tmp_d < d) {
                        c = p1;
                        d = tmp_d;
                    }

                    tmp_d = CGAL::squared_distance(p, p2);
                    if(tmp_d < d) {
                        c = p2;
                        d = tmp_d;
                    }
                }
                else {
                    K::Segment_2 s(p1, p2);
                    auto tmp = CGAL::intersection(r, s);
                    const K::Point_2* o = boost::get<K::Point_2>(&*tmp);
                    tmp_d = CGAL::squared_distance(p, *o);
                    if(!hit || tmp_d < d) {
                        c = *o;
                        d = tmp_d;
                    }
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
}
