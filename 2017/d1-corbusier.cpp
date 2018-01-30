#include<bits/stdc++.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, I, K;
        cin >> N >> I >> K;

        vector<vector<int> > dp(N+1, vector<int>(K, INT_MIN));
        dp[0][0] = 0;

        for(int in = 1; in < N+1; ++in) {
            int rh;
            cin >> rh;
            rh %= K;

            for(int ik = 0; ik < K; ++ik) {
                dp[in][ik] = max(dp[in-1][ik], dp[in-1][(K+ik-rh)%K]+1);
            }
        }

        cout << (dp[N][I] > 0 ? "yes" : "no") << endl;
    }

    return 0;
}
