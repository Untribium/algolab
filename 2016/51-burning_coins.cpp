#include<stdio.h>
#include<algorithm>

using namespace std;

int n;
int vals[2500];
int memo[2500][2500];

int best(int l, int r) {

    // base case
    if(l+1 >= r) {
        return max(vals[l], vals[r]);
    }

    // memo
    if(!memo[l][r]) {
        memo[l][r] = max(min(best(l+2, r), best(l+1, r-1))+vals[l], min(best(l+1, r-1), best(l, r-2))+vals[r]);
    }

    return memo[l][r];

}

void do_case(int t) {

    // #coins
    scanf("%i", &n);

    // read values
    for(int i = 0; i < n; ++i) {
        scanf("%i", &vals[i]);

        // reset memo table
        for(int j = 0; j < n; ++j) {
            memo[i][j] = 0;
        }
    }

    printf("%i\n", best(0, n-1));
}

int main() {
    int t;

    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }

    return 0;
}
