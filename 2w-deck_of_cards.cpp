#include<stdio.h>
#include<vector>

using namespace std;

int abs(int a) {
    return (a < 0) ? -a : a;
}

void do_case() {
    int n, k;
    scanf("%i %i", &n, &k);

    int ps[n+1];
    ps[0] = 0;

    for(int i = 1; i <= n; ++i) {
        int v;
        scanf("%i", &v);

        ps[i] = ps[i-1]+v;
    }

    int l = 0, r = 1;
    int min_l = 0, min_r = 1, min_d;
    min_d = abs(k-ps[1]);

    while(r <= n) {

        int d = abs(k-(ps[r]-ps[l]));

        if(d < min_d) {
            min_l = l;
            min_r = r;
            min_d = d;
        }

        while(ps[r]-ps[l] > k) {
            l++;

            d = abs(k-(ps[r]-ps[l]));

            if(d < min_d) {
                min_l = l;
                min_r = r;
                min_d = d;
            }
        }

        r++;
    }

    printf("%i %i\n", min_l, min_r-1);

}

int main() {

    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }

    return 0;
}
