#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N, M;
        cin >> N >> M;

        vector< pair<long long, long long> > j; // jedi
        vector< pair<long long, bool> > e; // endpoints

        for(int ij = 0; ij < N; ++ij) {
            long long a, b;
            cin >> a >> b;
            a--; b--;

            if(a > b) b += M;

            j.emplace_back(a, b);
            j.emplace_back(a+M, b+M);

            e.emplace_back(a, false);
            e.emplace_back(b+1, true);
            e.emplace_back(a+M, false);
            e.emplace_back(b+1+M, true);
        }

        sort(e.begin(), e.end());

        int bz = j.size(), be = 0, z = 0;

        for(pair<long long, bool> ee : e) {

            if(!ee.second) {
                z++;
            } else {
                z--;
                if(z < bz && ee.first >= M && ee.first < 2*M) {
                    bz = z;
                    be = ee.first;
                }
            }
        }

        vector< tuple<long long, long long, long long> > s;

        for(pair<long long, long long>& ej : j) {
            if(ej.first <= be && ej.second >= be) {
                s.emplace_back(ej.second, ej.first, 1);
            }

            ej = make_pair(ej.second, ej.first);
        }

        s.emplace_back(be, be, 0);

        int bc = 1;

        sort(j.begin(), j.end());

        for(tuple<long long, long long, long long> es : s) {
            int c = get<2>(es), l = get<1>(es), r = get<0>(es)-M;

            for(pair<long long, long long> ej : j) {
                if(ej.second > r && ej.first < l) {
                    c++;
                    r = ej.first;
                }
            }

            bc = max(bc, c);
        }

        cout << bc << endl;
    }

    return 0;

}
