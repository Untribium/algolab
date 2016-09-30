#include<stdio.h>
#include<vector>
#include<algorithm>

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

bool check(int l) {

    vector<int> cs(n, 0);
    int c = 0;

    int b = 0, e = 0; // begin, end

    while(e < (int)os.size()) {
        cs[os[e].w]++;

        if(cs[os[e].w] == 1) {
            c++;
        }

        while(os[e].p-os[b].p > l) {
            cs[os[b].w]--;
            if(!cs[os[b].w]) {
                c--;
            }
            b++;
        }

        if(c == n) {
            return true;
        }

        e++;
    }
    return false;
}

void do_case() {
    ms.clear();
    os.clear();

    scanf("%i", &n);

    for(int i = 0; i < n; ++i) {
        int m;
        scanf("%i", &m);

        ms.push_back(m);
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < ms[i]; ++j) {
            Occ o;
            o.w = i;
            scanf("%i", &o.p);

            os.push_back(o);
        }
    }

    sort(os.begin(), os.end());

    int min = 1, max = os.back().p;

    while(min != max) {
        int a = (min+max)/2;

        if(check(a)) {
            max = a;
        }
        else {
            min = a+1;
        }
    }
    printf("%i\n", max+1);
}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }
}
