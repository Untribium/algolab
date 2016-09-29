#include<vector>
#include<algorithm>
#include<stdio.h>
#include<math.h>

using namespace std;

vector<int> ss;
vector<int> ws;

void do_case() {
    int n, m;
    scanf("%i %i", &n, &m);

    // read strengths
    ss.clear();
    for(int i = 0; i < n; ++i) {
        int v;
        scanf("%i", &v);
        ss.push_back(v);
    }
    sort(ss.rbegin(), ss.rend());

    // read weights
    ws.clear();
    for(int i = 0; i < m; ++i) {
        int v;
        scanf("%i", &v);
        ws.push_back(v);
    }
    sort(ws.rbegin(), ws.rend());

    if(ws[0] > ss[0]) {
        printf("impossible\n");
        return;
    }

    // guys, rounds, excess
    long long g = 0, r = 0, e = 0;
    // indices
    int iw = 0, is = 0;

    while(iw < m) {
        int s = ss[is];
        long long cs = 0;

        for(; is < n && ss[is] == s; is++, cs++);

        int t = (is < n) ? ss[is] : 0;
        long long cw = 0;

        for(; iw < m && ws[iw] > t; iw++, cw++);

        g += cs;
        cw -= cs*r;

        e -= cw;

        if(e < 0) {
            e = -e;
            int ri = ((e-1)/g)+1;
            e = ri*g-e;
            r += ri;
        }
    }

    printf("%d\n", r*3-1);

}

int main() {
    int t;
    scanf("%i", &t);

    while (t--) {
        do_case();
    }

    return 0;
}
