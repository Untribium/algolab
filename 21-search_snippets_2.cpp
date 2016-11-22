#include<stdio.h>
#include<vector>
#include<algorithm>
#include<limits.h>

using namespace std;

struct Occ {
    int p; // position
    int w; // word
};

bool operator<(const Occ& o1, const Occ& o2) {
    return o1.p < o2.p;
}

int n;

vector<Occ> os;
vector<int> ms;

void do_case() {

    scanf("%i", &n);

    ms.resize(n);

    int l = 0;

    for(int i = 0; i < n; ++i) {
        scanf("%i", &ms[i]);
        l += ms[i];
    }

    os.resize(l);

    l = 0;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < ms[i]; ++j) {
            os[l].w = i;
            scanf("%i", &os[l].p);
            l++;
        }
    }

    sort(os.begin(), os.end());

    vector<int> cs(n, 0);
    int c = 0, d = 0, min_d = INT_MAX;

    int b = 0, e = 0; // begin, end

    while(e < os.size()) {
        cs[os[e].w]++;

        if(cs[os[e].w] == 1) {
            c++;
        }

        d = os[e].p-os[b].p;

        while(cs[os[b].w] > 1 && b < e) {
            cs[os[b].w]--;
            b++;
            d = os[e].p-os[b].p;
        }

        if(c == n) {
            min_d = min(min_d, d);
        }

        e++;
    }

    printf("%i\n", min_d+1);
}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }
}
