#include<stdio.h>
#include<vector>

using namespace std;

void do_case(int t) {

    int n, k;
    unsigned int x_;
    scanf("%i %i %u", &n, &k, &x_);

    int x[k];

    for(int i = 0; i < k; ++i) {
        x[i] = x_ & (1 << (k-(i+1))) ? 1 : 0;
    }

    vector<int> diff(n/k, 0);

    for(int i = 0; i < n; ++i) {

        int d;
        scanf("%i", &d);

        if(d != x[i%k]) {
            diff[i/k]++;
        }
    }

    int ops = 0;
    int state = -1;

    for(int i = 0; i < n/k; ++i) {

        int flips = diff[i];

        if(state == 0 && flips > k-flips+1) {
            state = 1;
            ops += k-flips+1;
        } else if(state == 0 && flips < k-flips+1) {
            state = 0;
            ops += flips;
        } else if(state == 0 && flips == k-flips+1) {
            state = -1;
            ops += flips;
        } else if(state == 1 && k-flips > flips+1) {
            state = 0;
            ops += flips+1;
        } else if(state == 1 && k-flips < flips+1) {
            state = 1;
            ops += k-flips;
        } else if(state == 1 && k-flips == flips+1) {
            state = -1;
            ops += k-flips;
        } else if(state == -1 && flips > k-flips) {
            state = 1;
            ops += k-flips;
        } else if(state == -1 && flips < k-flips) {
            state = 0;
            ops += flips;
        } else if(state == -1 && flips == k-flips) {
            state = -1;
            ops += flips;
        }
    }

    if(state == 1) {
        ops += 1;
    }

    printf("%i\n", ops);

}

int main() {

    int t;
    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }

    return 0;
}
