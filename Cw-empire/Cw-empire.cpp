#include<stdio.h>
#include<vector>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

#include<CGAL/basic.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
#include<CGAL/Gmpq.h>

#include<iostream>

using namespace std;
using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Delaunay_triangulation_2<K>                       Delaunay;
typedef K::Point_2                                              Point;

typedef CGAL::Gmpq                                              ET;

typedef CGAL::Quadratic_program<ET>                             LP;
typedef CGAL::Quadratic_program_solution<ET>                    Solution;

int t;

void do_case() {
    int a, s, b, e;
    scanf("%i %i %i %i", &a, &s, &b, &e);

    vector<pair<Point, int> > asteroids(a);

    for(int ia = 0; ia < a; ++ia) {
        int x, y, d;
        scanf("%i %i %i", &x, &y, &d);

        asteroids[ia] = make_pair(Point(x, y), d);
    }

    vector<pair<Point, K::FT> > spots(s);

    for(int is = 0; is < s; ++is) {
        int x, y;
        scanf("%i %i", &x, &y);

        spots[is] = make_pair(Point(x, y), -1);
    }

    vector<Point> hunters(b);

    for(int ib = 0; ib < b; ++ib) {
        int x, y;
        scanf("%i %i", &x, &y);

        hunters[ib] = Point(x, y);
    }

    Delaunay d;
    d.insert(hunters.begin(), hunters.end());

    LP lp(CGAL::LARGER, true, 0, false, 0);

    for(int is = 0; is < s; ++is) {
        if(b) {
            spots[is].second = CGAL::squared_distance(spots[is].first, d.nearest_vertex(spots[is].first)->point());
        }
        lp.set_c(is, 1);
    }

    for(int ia = 0; ia < a; ++ia) {

        lp.set_b(ia, asteroids[ia].second);

        for(int is = 0; is < s; ++is) {

            K::FT distance = squared_distance(spots[is].first, asteroids[ia].first);

            if(spots[is].second == -1 || distance < spots[is].second) {
                if(distance > 1) {
                    lp.set_a(is, ia, 1/ET(distance));
                } else {
                    lp.set_a(is, ia, 1);
                }

            } else {
                lp.set_a(is, ia, 0);
            }
        }
    }

    Solution result = solve_linear_program(lp, ET());

    if(result.is_infeasible() || result.objective_value() > e) {
        printf("n\n");
    } else {
        printf("y\n");
    }

}

int main() {
    scanf("%i", &t);

    while (t--) {
        do_case();
    }

    return 0;
}
