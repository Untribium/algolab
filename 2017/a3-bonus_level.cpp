#include<bits/stdc++.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<vector<int> > coins(N, vector<int>(N, 0));

        for(auto &ecoins : coins) {
            for(int &eecoins : ecoins) {
                cin >> eecoins;
            }
        }

        vector<vector<vector<int> > > dp(2*N-1, vector<vector<int> >(N, vector<int>(N, 0)));
        dp[0][0][0] = coins[0][0];

        for(int kdp = 1; kdp < N; ++kdp) {
            for(int idp = 0; idp <= kdp; ++idp) {
                for(int jdp = 0; jdp <= kdp; ++jdp) {

                    int v, c = coins[idp][kdp-idp];
                    if(idp != jdp) c += coins[jdp][kdp-jdp];                // same shelf

                    v = dp[kdp-1][idp][jdp];                                // right, right
                    if(idp) v = max(v, dp[kdp-1][idp-1][jdp]);              // down,  right
                    if(jdp) v = max(v, dp[kdp-1][idp][jdp-1]);              // right, down
                    if(idp && jdp) v = max(v, dp[kdp-1][idp-1][jdp-1]);     // down,  down

                    dp[kdp][idp][jdp] = v+c;
                }
            }
        }

        for(int kdp = N; kdp < 2*N-1; ++kdp) {
            for(int idp = kdp-N+1; idp < N; ++idp) {
                for(int jdp = kdp-N+1; jdp < N; ++jdp) {

                    int v, c = coins[idp][kdp-idp];
                    if(idp != jdp) c += coins[jdp][kdp-jdp];                // same shelf

                    v = dp[kdp-1][idp-1][jdp-1];                            // down,  down
                    v = max(v, dp[kdp-1][idp-1][jdp]);                      // down,  right
                    v = max(v, dp[kdp-1][idp][jdp-1]);                      // right, down
                    v = max(v, dp[kdp-1][idp][jdp]);                        // right, right

                    dp[kdp][idp][jdp] = v+c;
                }
            }
        }

        cout << dp[2*N-2][N-1][N-1] << endl;
    }

    return 0;
}
