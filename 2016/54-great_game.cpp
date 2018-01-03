#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;

vector< vector<int> > e;

void do_case(int t) {

    int n, m;
    scanf("%i %i", &n, &m);

    e.assign(n, vector<int>(0));

    int r, b;
    scanf("%i %i", &r, &b);
    r -= 1;
    b -= 1;

    for(int i = 0; i < m; ++i) {

        int from, to;
        scanf("%i %i", &from, &to);

        e[from-1].push_back(to-1);
    }

    vector<int> best(n, 1000000);
    vector<int> worst(n, -1);

    best[n-1] = 0;
    worst[n-1] = 0;

    for(int i = n-2; i >= 0; --i) {

        for(int edge : e[i]) {
            if(worst[edge] < best[i]) {
                best[i] = worst[edge];
            }

            if(best[edge] > worst[i]) {
                worst[i] = best[edge];
            }
        }

        best[i]++;
        worst[i]++;
    }

    // for(int i = 0; i < n; ++i) {
    //     printf("%i: %i %i\n", i, best[i], worst[i]);
    // }

    if(best[r] < best[b]) {
        printf("0\n");
    } else if(best[b] < best[r]) {
        printf("1\n");
    } else if(best[r] == best[b]) {
        printf("%i\n", (best[r]+1)%2);
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
