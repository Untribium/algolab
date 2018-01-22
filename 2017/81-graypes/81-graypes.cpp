#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel   K;
typedef Point_2<K>                                      P2;
typedef Segment_2<K>                                    S2;
typedef Delaunay_triangulation_2<K>                     DT;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {

        int N;
        cin >> N;

        if(!N) break;

        vector<P2> g(N);

        for(P2 &eg : g) {
            long long x, y;
            cin >> x >> y;

            eg = P2(x, y);
        }

        DT t;
        t.insert(g.begin(), g.end());

        double d = HUGE_VAL;

        for(DT::Finite_edges_iterator it = t.finite_edges_begin(); it != t.finite_edges_end(); ++it) {
            S2 s = t.segment(it);
            d = std::min(d, to_double(s.squared_length()));
        }

        cout << ceil(std::sqrt(d)/2*100) << endl;
    }

    return 0;
}
