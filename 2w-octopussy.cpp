#include<stdio.h>
#include<algorithm>
#include<vector>
#include<math.h>
#include<queue>
#include<limits.h>

using namespace std;

struct Bomb {
    Bomb(int p_i, int p_t) {
        i = p_i;
        t = p_t;
    }
    int i;
    int t;
    int m;
};

bool operator<(const Bomb& b1, const Bomb& b2) {
    return b1.m > b2.m;
}

int n;

vector<Bomb> bs;
vector<bool> ds;
priority_queue<Bomb> q;

int dfs(Bomb* b, int m) {
    int i = 2*b->i;
    m = min(m, b->t);
    b->m = m;

    if(i+2 < n) {
        dfs(&bs[i+1], m-1);
        dfs(&bs[i+2], m-1);
    }
}

void do_case() {
    scanf("%i", &n);

    bs.clear();
    for(int i = 0; i < n; ++i) {
            int t;
            scanf("%i", &t);
            bs.push_back(Bomb(i, t));
    }

    if(n==1) {
        printf("yes\n");
        return;
    }

    dfs(&bs[0], INT_MAX);

    // clear queue
    while(q.size()) {
        q.pop();
    }

    for(int i = (n-1)/2; i < n; ++i) {
        q.push(bs[i]);
    }

    int t = 0;

    ds.assign(n, false);

    while (q.size()) {
        Bomb c = q.top();
        ds[c.i] = true;
        q.pop();

        if(c.t <= t) {
            printf("no\n");
            return;
        }

        if(c.i == 0) {
            break;
        }

        if(c.i%2 == 0) {
            if(ds[c.i-1]) {
                q.push(bs[c.i/2-1]);
                // printf("push: %i %i\n", c.i/2-1, bs[c.i/2-1].m);
            }
        }
        else {
            if(ds[c.i+1]) {
                q.push(bs[c.i/2]);
                // printf("push: %i %i\n", c.i/2, bs[c.i/2].m);
            }
        }

        t++;

    }

    printf("yes\n");

}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }

    return 0;

}
