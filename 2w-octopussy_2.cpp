#include<vector>
#include<stdio.h>
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

    ts.assign(n, 0);

    while(q.size()) {
        q.pop();
    }

    scanf("%i", &ts[0]);

    for(int i = 1; i < n; ++i) {
        scanf("%i", &ts[i]);
        ts[i] = min(ts[i], ts[(i-1)/2]-1);
        if(i >= (n-1)/2) {
            q.push(Bomb(i));
        }
    }

    int t = 0;
    ds.assign(n, false);

    while(q.size() && t < n-1) {
        int i = q.top().i;
        q.pop();
        ds[i] = true;

        if(ts[i] <= t) {
            printf("no\n");
            return;
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
