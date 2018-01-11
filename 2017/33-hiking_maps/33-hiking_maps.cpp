#include<iostream>
#include<vector>
#include<limits.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Point_2<K> P2;
typedef Segment_2<K> S2;

bool contains(vector<P2>& et, P2 p) {
    return !right_turn(et[0], et[1], p) &&
           !right_turn(et[2], et[3], p) &&
           !right_turn(et[4], et[5], p);
}

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int M, N;
        cin >> M >> N;

        vector<S2> s(M-1);

        int ax, ay, bx, by;
        cin >> ax >> ay;

        for(S2 &es : s) {
            cin >> bx >> by;

            es = S2(P2(ax, ay), P2(bx, by));

            ax = bx; ay = by;
        }

        vector< vector<P2> > t(N, vector<P2>(6));

        for(vector<P2> &et : t) {
            for(P2 &eet : et) {
                int x, y;
                cin >> x >> y;
                eet = P2(x, y);
            }

            if(right_turn(et[0], et[1], et[2])) swap(et[0], et[1]);
            if(right_turn(et[2], et[3], et[4])) swap(et[2], et[3]);
            if(right_turn(et[4], et[5], et[0])) swap(et[4], et[5]);
        }

        vector< vector<int> > c(N);

        for(int it = 0; it < t.size(); ++it) {
            for(int is = 0; is < s.size(); ++is) {
                if(contains(t[it], s[is].source()) && contains(t[it], s[is].target())) {
                    c[it].push_back(is);
                }
            }
        }

        int v = 0;
        vector<int> g(s.size(), 0);
        int l = 0, r = -1;
        int b = t.size()-1, bl = 0, br = t.size()-1;

        while(true) {
            if(v == s.size() && l < r) {
                for(int ec : c[l]) {
                    if(!--g[ec]) {
                        v--;
                    }
                }
                l++;
            } else {
                if(++r == t.size()) break;

                for(int ec : c[r]) {
                    if(!g[ec]++) {
                        v++;
                    }
                }
            }

            if(v == s.size() && r-l < b) {
                bl = l;
                br = r;
                b = r-l;
            }
        }

        cout << b+1 << endl;
    }

    return 0;
}
