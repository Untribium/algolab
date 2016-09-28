#include<stdio.h>
#include<limits.h>
#include<math.h>
#include<vector>
#include<algorithm>

using namespace std;

struct Boat {
    int l;
    int p;

    bool operator<(const Boat& b) const { return p < b.p; }
};

vector< Boat > bs;

void do_case() {
    int n;
    scanf("%i", &n);

    for(int i = 0; i < n; ++i) {
        Boat b;
        scanf("%i %i", &b.l, &b.p);

        bs.push_back(b);
    }

    sort(bs.begin(), bs.end());

    // for(Boat b : bs) {
    //     printf("%i %i\n", b.p, b.l);
    // }

    int c = 0, p = INT_MIN, l = INT_MIN;

    for(int i = 0; i < n; ++i) {
        Boat b = bs[i];
        if(b.p >= p) {
            c++;
            l = p;
            p = max(b.p, p+b.l);
            // printf("take %i, p: %i\n", b.p, p);
        }
        else if(max(b.p, l+b.l) < p) {
            p = max(b.p, l+b.l);
            // printf("drop last, take %i, new p: %i\n", b.p, p);
        }
    }

    printf("%i\n", c);

    bs.clear();

}

int main() {

    int t;
    scanf("%i", &t);

    while (t--) {
        do_case();
    }

    return 0;
}
