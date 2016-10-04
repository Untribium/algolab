#include<vector>
#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<queue>

using namespace std;

struct Bomb {
    Bomb(int p_i) {
        i = p_i;
    }
    int i;
};

vector<int> ts;
vector<bool> ds;

bool operator<(const Bomb& b1, const Bomb& b2) {
    return ts[b1.i] > ts[b2.i];
}

priority_queue<Bomb> q;

void do_case() {
    int n;
    scanf("%i", &n);

    if(n == 1) {
        printf("yes\n");
        return;
    }

    ts.assign(n, 0);

    for(int i = 0; i < n; ++i) {
        scanf("%i", &ts[i]);
    }

    for(int i = 1; i < n; ++i) {
        ts[i] = min(ts[i], ts[(i-1)/2]-1);
    }

    while(q.size()) {
        q.pop();
    }

    for(int i = (n-1)/2; i < n; ++i) {
        q.push(Bomb(i));
    }

    int t = 0;
    ds.assign(n, false);

    while(q.size()) {
        int i = q.top().i;
        q.pop();
        ds[i] = true;

        if(ts[i] <= t) {
            printf("no\n");
            return;
        }

        if(i == 0) {
            break;
        }

        if(ds[i+((i%2)*2-1)]) {
            q.push(Bomb((i-1)/2));
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
}
