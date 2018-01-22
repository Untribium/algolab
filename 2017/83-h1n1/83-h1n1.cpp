#include<iostream>
#include<unordered_map>
#include<queue>
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

        int N;
        cin >> N;

        if(!N) break;

        vector<P2> p(N);

        for(int ip = 0; ip < (int) p.size(); ++ip) {
            int x, y;
            cin >> x >> y;

            p[ip] = P2(x, y);
        }

        DT t;
        t.insert(p.begin(), p.end());

        unordered_map<DT::Face_handle, vector<pair<DT::Face_handle, long long> > > m;

        for(auto it = t.finite_faces_begin(); it != t.finite_faces_end(); ++it) {
            for(int i = 0; i < 3; ++i) {
                long long w = squared_distance(it->vertex((i+1)%3)->point(), it->vertex((i+2)%3)->point());
                m[it].emplace_back(it->neighbor(i), w);
            }
        }

        bool k = t.finite_faces_begin() == t.finite_faces_end();

        int M;
        cin >> M;

        for(int ie = 0; ie < M; ++ie) {
            int x, y; long long d;
            cin >> x >> y >> d;

            P2 e(x, y);

            if(squared_distance(t.nearest_vertex(e)->point(), e) < d) {
                cout << "n";
                continue;
            } else if(k) {
                cout << "y";
                continue;
            }

            unordered_map<DT::Face_handle, bool> v;
            queue<DT::Face_handle> q;

            DT::Face_handle f = t.locate(e);
            q.push(f);
            v[f] = true;

            while(q.size()) {
                f = q.front();
                q.pop();

                if(t.is_infinite(f)) break;

                for(auto em : m[f]) {
                    if(d*4 <= em.second && !v[em.first]) {
                        q.push(em.first);
                        v[em.first] = true;
                    }
                }
            }

            cout << (t.is_infinite(f) ? "y" : "n");
        }

        cout << endl;
    }

    return 0;
}
