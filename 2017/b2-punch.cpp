#include<bits/stdc++.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, K;
        cin >> N >> K;

        vector<int> v(N), c(N);

        for(int in = 0; in < N; ++in) cin >> c[in] >> v[in];

        vector<vector<pair<int, int> > > dp(N, vector<pair<int, int> >(K, make_pair(INT_MAX, 0)));

        for(int ik = 0; ik < K; ++ik) {
            dp[0][ik] = make_pair((ik/v[0]+1)*c[0], -1);
        }

        for(int in = 1; in < N; ++in) {
            for(int ik = 0; ik < K; ++ik) {

                if(ik < v[in]) {
                    dp[in][ik] = min(make_pair(c[in], -1), dp[in-1][ik]);
                    continue;
                }

                pair<int, int> b, m;

                b = dp[in][ik-v[in]];
                b.first += c[in];
                m = min(b, dp[in-1][ik]);

                b = dp[in-1][ik-v[in]];
                b.first += c[in]; b.second -= 1;

                dp[in][ik] = min(b, m);
            }
        }

        cout << dp[N-1][K-1].first << " " << -dp[N-1][K-1].second << endl;
    }

    return 0;
}
