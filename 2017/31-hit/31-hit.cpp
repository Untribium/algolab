#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2   P;
typedef K::Segment_2 S;

int main() {

    while(true) {
        int N;
        cin >> N;

        if(!N) break;

        long double px, py, qx, qy;
        cin >> px >> py >> qx >> qy;

        K::Ray_2 r(P(px, py), P(qx, qy));

        bool h = false;

        while(N--) {
            long double ax, ay, bx, by;
            cin >> ax >> ay >> bx >> by;

            if(!h) {
                h = do_intersect(r, S(P(ax, ay), P(bx, by)));
            }
        }

        if(h) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
