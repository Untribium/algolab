#include<stdio.h>
#include<vector>

using namespace std;

bool debug = false;

int bitmaps[31][5];

void precomp() {
    for(int i = 1; i < 32; ++i) {
        for(int j = 0; j < 5; ++j) {
            bitmaps[i-1][j] = (i>>j)%2;
        }
    }
}

void do_case(int t) {
    int n;
    scanf("%i", &n);

    vector<int> ms(n, 0);
    vector<int> factors(n, 1);

    int l = 1;

    for(int i = 0; i < n; ++i) {
        scanf("%i", &ms[i]);
        ms[i]++;
        factors[i] = l;
        l *= ms[i];
    }

    vector<int> offsets((1<<n)-1, 0);

    for(int i = 0; i < (int) offsets.size(); ++i) {
        for(int j = 0; j < n; ++j) {
            offsets[i] += bitmaps[i][j]*factors[j];
        }
    }

    vector<vector<int> > stacks;

    for(int i = 0; i < n; ++i) {
        stacks.push_back(vector<int>(ms[i], 0));
        for(int j = 1; j < ms[i]; ++j) {
            scanf("%i", &stacks[i][j]);
        }
    }

    if(n == 1) {
        printf("0\n");
        return;
    }

    vector<vector<int> > state(l, vector<int>(n, 0));

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < l; j++) {
            state[j][i] = (j/factors[i])%ms[i];
        }
    }

    vector<int> memo(l, 0);

    for(int i = 1; i < l; ++i) {
        for(int j = 0; j < (int) offsets.size(); ++j) {

            if(i-offsets[j] >= 0) {

                vector<int> n_state = state[i];

                int k, c = 0, count = 0;
                for(k = 0; k < n; ++k) {

                    if(bitmaps[j][k]) {
                        count++;

                        if(state[i][k] == 0) {
                            break;
                        } else {
                            if(c) {
                                if(c != stacks[k][n_state[k]]) {
                                    break;
                                }
                            } else {
                                c = stacks[k][n_state[k]];
                            }
                        }
                    }
                }

                if(k != n) {
                    continue;
                }

                memo[i] = max(memo[i], memo[i-offsets[j]]+max(1<<(count-2), 0));
            }
        }
    }

    printf("%i\n", memo[l-1]);
}

int main() {

    precomp();

    int t;
    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }
}
