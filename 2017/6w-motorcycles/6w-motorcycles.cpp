#include<iostream>
#include<algorithm>
#include<tuple>
#include<vector>
#include<limits.h>

using namespace std;

typedef unsigned long long ulolo;

struct rider {
    uint ax, bx, ay, by;
    bool f;
    long long o;
    int i;
};

tuple<ulolo, ulolo, bool> mult(const rider &r1, const rider &r2) {
    // cout << r1.ax << " " << r2.ay << " " << (r1.f ? "true" : "false") << " " << (r2.f ? "true" : "false") << endl;

    ulolo q1, q2, g0, g1, g2;

    g0 = r1.ay * r2.ax;
    g1 = r1.ay * r2.bx;
    g2 = r1.by * r2.ax;

    q1 = g0 + (g1 << 32) + (g2 << 32);
    q2 = r1.by * r2.bx;

    return make_tuple(q1, q2, r1.f);
}

bool operator<(const rider &r1, const rider &r2) {
    return mult(r1, r2) < mult(r2, r1);
}

bool operator!=(const rider &r1, const rider &r2) {
    return mult(r1, r2) != mult(r2, r1);
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<rider> d(N);

        for(int in = 0; in < N; ++in) {
            long long x, y;
            cin >> d[in].o >> x >> y;

            d[in].f = (y < d[in].o);
            y = d[in].f ? d[in].o - y : y - d[in].o;

            d[in].ax = x & UINT_MAX;
            d[in].bx = x >> 32;
            d[in].ay = y & UINT_MAX;
            d[in].by = y >> 32;

            d[in].i = in;

            // d[in] = make_tuple(D2(x, (y < o ? o-y : y-o)), (y < o), o, in);
        }

        sort(d.begin(), d.end());

        // for(auto ed : d) {
        //     cout << ed.i << endl;
        // }

        vector<int> r;

        rider l, c;
        // D2 dl, dc; bool fl, fc; long long ol, oc; int il, ic;

        long long tho, ho = tho = LLONG_MIN, tlo, lo = tlo = LLONG_MAX;

        for(int in = 0; in < N; in++) {

            // tie(dc, fc, oc, ic) = d[in];
            c = d[in];

            if(l != c) {
                ho = std::max(ho, tho);
                lo = std::min(lo, tlo);
            }

            // if(dc != dl || fc != fl) {
            //     ho = std::max(ho, tho);
            //     lo = std::min(lo, tlo);
            // }

            if((c.f && c.o < lo) || (!c.f && c.o > ho)) {
                r.push_back(c.i);
            }

            // if(fc && oc < lo || !fc && oc > ho) {
            //     r.push_back(ic);
            // }

            tlo = std::min(tlo, c.o);
            tho = std::max(tho, c.o);

            l = c;

            // dl = dc; fl = fc;

        }

        sort(r.begin(), r.end());

        for(int er : r) {
            cout << er << " ";
        }

        cout << endl;
    }

    return 0;
}
