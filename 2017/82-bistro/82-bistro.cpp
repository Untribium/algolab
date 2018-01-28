#include<bits/stdc++.h>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel       K;
typedef Point_2<K>                                          P2;
typedef Delaunay_triangulation_2<K>                         DT;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {

        int N, M;
        cin >> N;

        if(!N) return 0;

        vector<P2> p(N);

        for(P2 &ep : p) cin >> ep;

        DT t;
        t.insert(p.begin(), p.end());

        cin >> M;

        for(int im = 0; im < M; ++im) {
            P2 r;
            cin >> r;

            cout << (long long) squared_distance(t.nearest_vertex(r)->point(), r) << endl;
        }
    }
}
