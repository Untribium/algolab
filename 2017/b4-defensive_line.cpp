#include<bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> tiii;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, K;
        cin >> N >> M >> K;

        vector<int> s(N);

        for(int &es : s) cin >> es;

        vector<pair<int, int> > i;
        i.push_back(make_pair(0, 0)); // dummy to "fix" index

        int l = 0, r = -1, c = 0;

        while(true) {
            if (c < K || l >= r) {
                if(++r >= N) break;
                c += s[r];
            } else {
                c -= s[l++];
            }

            if(c == K) i.emplace_back(l, r);
        }

        if(M > (int) i.size()) {
            cout << "fail" << endl;
            continue;
        }

        vector<vector<tiii> > dp(M+1, vector<tiii>(i.size(), make_tuple(0, 1, 0)));

        for(int idp = 1; idp < (int) dp.size(); ++idp) {

            int kdp = idp-1;

            for(int jdp = idp; jdp < (int) dp[0].size(); ++jdp) {

                // move along last row
                while(kdp < jdp && -get<1>(dp[idp-1][kdp+1]) < i[jdp].first) {
                    kdp++;
                }

                if(-get<1>(dp[idp-1][kdp]) < i[jdp].first) {
                    get<0>(dp[idp][jdp]) = get<0>(dp[idp-1][kdp])+i[jdp].second-i[jdp].first+1;
                    get<1>(dp[idp][jdp]) = -i[jdp].second;
                    get<2>(dp[idp][jdp]) = get<2>(dp[idp-1][kdp])+1;
                }

                dp[idp][jdp] = max(dp[idp][jdp], dp[idp][jdp-1]);
            }
        }

        int out = get<0>(dp[M][i.size()-1]);
        if(out && get<2>(dp[M][i.size()-1]) == M) {
            cout << out << endl;
        } else {
            cout << "fail" << endl;
        }

    }

    return 0;
}
