#include<iostream>
#include<algorithm>
#include<vector>
#include<limits.h>

using namespace std;

struct rider {
    uint ax, bx, ay, by;
    long long x, y;
    bool f;
    long long o;
    int i;
};

bool operator<(const rider &r1, const rider &r2) {
    __int128_t v1 = (__int128_t) r1.y * r2.x;
    __int128_t v2 = (__int128_t) r1.x * r2.y;
    return v1 == v2 ? r1.f < r2.f : v1 < v2;
}

bool operator!=(const rider &r1, const rider &r2) {
    __int128_t v1 = (__int128_t) r1.y * r2.x;
    __int128_t v2 = (__int128_t) r1.x * r2.y;
    return v1 != v2 || r1.f != r2.f;
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

            d[in].x = x;
            d[in].y = y;

            d[in].i = in;
        }

        sort(d.begin(), d.end());

        vector<int> r;

        rider l, c;

        long long tho, ho = tho = LLONG_MIN, tlo, lo = tlo = LLONG_MAX;

        for(int in = 0; in < N; in++) {

            c = d[in];

            if(in && l != c) {
                ho = std::max(ho, tho);
                lo = std::min(lo, tlo);
            }

            if((c.f && c.o < lo) || (!c.f && c.o > ho)) {
                r.push_back(c.i);
            }

            tlo = std::min(tlo, c.o);
            tho = std::max(tho, c.o);

            l = c;
        }

        sort(r.begin(), r.end());

        for(int er : r) {
            cout << er << " ";
        }

        cout << endl;
    }

    return 0;
}
