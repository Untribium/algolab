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

        unordered_map<DT::Face_handle, vector<pair<long long, DT::Face_handle> > > m;
        priority_queue<pair<long long, DT::Face_handle> > q;
        unordered_map<DT::Face_handle, long long> b;

        for(auto it = t.all_faces_begin(); it != t.all_faces_end(); ++it) {
            if(t.is_infinite(it)) {
                q.emplace(LLONG_MAX, it); continue;
            }

            for(int i = 0; i < 3; ++i) {
                long long w = squared_distance(it->vertex((i+1)%3)->point(), it->vertex((i+2)%3)->point());
                DT::Face_handle f = it->neighbor(i);

                if(t.is_infinite(f)) {
                    m[f].emplace_back(w, it);
                } else {
                    m[it].emplace_back(w, f);
                }
            }
        }

        while(q.size()) {
            pair<long long, DT::Face_handle> top = q.top();
            q.pop();

            if(b.find(top.second) != b.end()) continue;

            b[top.second] = top.first;

            for(auto em : m[top.second]) {
                if(b.find(em.second) != b.end()) continue;
                q.emplace(std::min(em.first, top.first), em.second);
            }
        }

        int M;
        cin >> M;

        for(int ie = 0; ie < M; ++ie) {
            int x, y; long long d;
            cin >> x >> y >> d;

            P2 e(x, y);

            if(squared_distance(t.nearest_vertex(e)->point(), e) < d) {
                cout << "n"; continue;
            }

            cout << (b[t.locate(e)] >= d*4 ? "y" : "n");
        }

        cout << endl;
    }

    return 0;
}
