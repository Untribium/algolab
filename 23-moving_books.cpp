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
    // reverse sort
    sort(ss.rbegin(), ss.rend());

    // read weights
    ws.clear();
    for(int i = 0; i < m; ++i) {
        int v;
        scanf("%i", &v);
        ws.push_back(v);
    }
    // reverse sort
    sort(ws.rbegin(), ws.rend());

    // if highest weight < highest strength
    if(ws[0] > ss[0]) {
        printf("impossible\n");
        return;
    }

    // guys, rounds, excess
    long long g = 0, r = 0, e = 0;
    // indices (weights, strengths)
    int iw = 0, is = 0;

    // iterate over all boxes
    while(iw < m) {

        // current highest strength
        int s = ss[is];
        // count of guys
        long long cs = 0;

        // count all guys with strength=s
        for(; is < n && ss[is] == s; is++, cs++);

        // threshold: look at remaining guys
        // t=smallest weight they *cannot* handle
        // so every weight>t has to be handled by current guys
        int t = (is < n) ? ss[is] : 0;

        // count of weights
        long long cw = 0;

        // count all boxes with weight>t
        for(; iw < m && ws[iw] > t; iw++, cw++);

        // capacity of current group assuming no change in rounds
        // subtract that from current group of boxes
        cw -= cs*r;

        // calculate excess capacity
        // keep in mind that potentially cw<0, in which case e is increased!
        // otherwise, use excess for current group
        e -= cw;

        // add current guys to total guys
        g += cs;

        // if excess is now negative, then we need more rounds
        if(e < 0) {

            // additional rounds needed. Note that all g guys are helping!
            int ri = ((-e-1)/g)+1;

            // calculate new excess (always >= 0)
            e = ri*g+e;

            // add new rounds to total
            r += ri;
        }
    }

    // time is rounds*3-1
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
