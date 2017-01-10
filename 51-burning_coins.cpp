#include<stdio.h>
#include<vector>

using namespace std;

void do_case(int t) {

    // #coins
    int n;
    scanf("%i", &n);

    // values
    vector<int> vs(n, 0);

    // dp array
    vector< vector<int> > dp(n+1, vector< int >(n+1, 0));

    // read values
    for(int i = 0; i < n; ++i) {
        scanf("%i", &vs[i]);

        dp[0][i] = -1000;
        dp[i][0] = -1000;
    }

    // rounds, look at diagonals
    for(int i = 1; i < n; ++i) {
        for(int l = 0; l < n; ++l) {

        }
    }
}

int main() {
    int t;

    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }

    return 0;
}
