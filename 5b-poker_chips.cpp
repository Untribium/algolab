#include<stdio.h>
#include<vector>
#include<set>

using namespace std;

bool debug = false;
// bool debug = false;

vector<int> factors;
vector< vector<int> > stacks;
vector<int> memo;

int index(const vector<int> state) {
    int index = 0;

    for(int i = 0; i < 5; ++i) {
        index += state.at(i)*factors.at(i);
    }

    return index;
}

int take(vector<int> state) {

    if(memo.at(index(state)) != -1) {
        // printf("memo\n");
        return memo.at(index(state));
    }

    // set<int> colors;
    //
    // int nonzero = 0;
    //
    // for(int i = 0; i < 5; ++i) {
    //     if(stacks.at(i).at(state.at(i))) {
    //         colors.insert(stacks.at(i).at(state.at(i)));
    //         nonzero++;
    //     }
    // }
    //
    // if(nonzero < 2) {
    //     memo.at(index(state)) = 0;
    //     return 0;
    // }

    int score = 0;

    // for(int c : colors) {
    //     vector<int> c_state;
    //     int k = 0;
    //
    //     for(int i = 0; i < 5; ++i) {
    //         c_state.push_back(state.at(i));
    //
    //         if(stacks.at(i).at(state.at(i)) == c) {
    //             c_state.at(i)--;
    //             k++;
    //         }
    //     }
    //
    //     if(k > 1) {
    //         score = max(score, take(c_state)+(1<<(k-2)));
    //     } else {
    //         score = max(score, take(c_state));
    //     }
    // }

    for(int i = 0; i < 32; ++i) {
        int color = 0;

        for(int j = 0; j < 5; ++j) {
            if((i>>j)%2) {
                color = stacks.at(j).at(state.at(j));
            }
        }

        if(!color) {
            continue;
        }

        vector<int> c_state;
        int k = 0;

        for(int j = 0; j < 5; ++j) {
            c_state.push_back(state.at(j));

            if((i>>j)%2) {
                if(color != stacks.at(j).at(state.at(j))) {
                    color = 0;
                    break;
                } else {
                    c_state.at(j)--;
                    k++;
                }
            }
        }

        if(!color) {
            continue;
        }

        if(memo.at(index(c_state)) == -1) {
            take(c_state);
        }

        if(k > 1) {
            score = max(score, memo.at(index(c_state))+(1<<(k-2)));
        } else {
            score = max(score, memo.at(index(c_state)));
        }
    }

    memo.at(index(state)) = score;
    return score;
}

void do_case(int t) {

    int n;
    scanf("%i", &n);

    vector<int> ms(5, 0);
    factors.assign(5, 1);

    int l = 1;

    for(int i = 0; i < n; ++i) {
        scanf("%i", &ms.at(i));
        factors.at(i) = l;
        l *= ms.at(i)+1;
    }

    memo.assign(l, -1);
    stacks.clear();

    for(int i = 0; i < 5; ++i) {
        // add extra '0'-chip to simplify code
        stacks.push_back(vector<int>(ms.at(i)+1, 0));

        for(int j = 1; j <= ms.at(i); ++j) {
            scanf("%i", &stacks.at(i).at(j));
        }
    }

    // score is 0 for 1 chip, therefore if n = 1 then score = 0
    if(n == 1) {
        printf("0\n");
        return;
    }

    printf("%i\n", take(ms));
}

int main() {
    for(int i = 0; i < 5; ++i) {
        stacks.push_back(vector<int>(0));
    }

    int t;
    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }

    return 0;
}
