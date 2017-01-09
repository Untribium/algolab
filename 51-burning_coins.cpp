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
    vector< vector< pair<int, int> > > dp(n, vector< pair<int, int> >(n, make_pair<int, int>(0, 0)));

    // read values
    for(int i = 0; i < n; ++i) {
        scanf("%i", &vs[i]);
    }

    // rounds, look at diagonals
    for(int i = 0; i < n; ++i) {

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
