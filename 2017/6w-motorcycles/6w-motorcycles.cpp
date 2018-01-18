#include<iostream>
#include<algorithm>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;

typedef Point_2<K> P2;
typedef Direction_2<K> D2;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<tuple<D2, bool, long long, int> > d(N);

        for(int in = 0; in < N; ++in) {
            long long o, x, y, dy;
            cin >> o >> x >> y;

            d[in] = make_tuple(D2(x, (y < o ? o-y : y-o)), (y < o), o, in);
        }

        sort(d.begin(), d.end());

        vector<int> r;

        D2 dl, dc; bool fl, fc; long long ol, oc; int il, ic;

        long long tho, ho = tho = LLONG_MIN, tlo, lo = tlo = LLONG_MAX;

        for(int in = 0; in < N; in++) {

            tie(dc, fc, oc, ic) = d[in];

            if(dc != dl || fc != fl) {
                ho = std::max(ho, tho);
                lo = std::min(lo, tlo);
            }

            if(fc && oc < lo || !fc && oc > ho) {
                r.push_back(ic);
            }

            tlo = std::min(tlo, oc);
            tho = std::max(tho, oc);

            dl = dc; fl = fc;

        }

        sort(r.begin(), r.end());

        for(int er : r) {
            cout << er << " ";
        }

        cout << endl;
    }

    return 0;
}
