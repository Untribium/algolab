#include<bits/stdc++.h>

using namespace std;

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

        vector<int> b(i.size(), 0); // last compatible interval (1-based!)
        l = 0;

        for(int ii = 1; ii < (int) i.size(); ++ii) {
            while(true) {
                b[ii] = l;
                if(i[l+1].second < i[ii].first) l++;
                else break;
            }
        }

        vector<vector<int> > dp(M, vector<int>(i.size(), 0));

        for(int jdp = 1; jdp < (int) i.size(); ++jdp) {
            dp[0][jdp] = max(dp[0][jdp-1], i[jdp].second-i[jdp].first+1);
        }

        for(int idp = 1; idp < M; ++idp) {
            for(int jdp = 1; jdp < (int) i.size(); ++jdp) {
                dp[idp][jdp] = dp[idp][jdp-1];
                if(b[jdp] && dp[idp-1][b[jdp]]) {
                    dp[idp][jdp] = max(dp[idp][jdp], dp[idp-1][b[jdp]]+i[jdp].second-i[jdp].first+1);
                }
            }
        }

        if(dp[M-1][i.size()-1]) {
            cout << dp[M-1][i.size()-1] << endl;
        } else {
            cout << "fail" << endl;
        }
    }

    return 0;
}
