#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<int> c(N);

        for(int &ec : c) cin >> ec;

        vector<pair<int, int> > o;

        for(int in = 0; in < N; ++in) {
            for(int ic = 0; ic < c[in]; ++ic) {
                int p;
                cin >> p;

                o.emplace_back(p, in);
            }
        }

        c.assign(N, 0);
        sort(o.begin(), o.end());

        int i = 0, l = 0, r = -1, b = INT_MAX;

        while(true) {

            if(i < N || l >= r) {
                if(++r >= (int) o.size()) break;
                if(!(c[o[r].second]++)) i++;
            } else {
                if(!(--c[o[l++].second])) i--;
            }

            if(i == N) {
                b = min(b, o[r].first-o[l].first+1);
            }
        }

        cout << b << endl;
    }

    return 0;
}
