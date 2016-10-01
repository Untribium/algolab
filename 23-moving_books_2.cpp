#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> ws;
vector<int> ss;
int s, w;

bool check(int r) {
    int is = 0, iw = 0;

    while(is < s && iw < w) {

        if(ss[is] < ws[iw]) {
            return false;
        }

        iw += r;
        is++;
    }

    return (iw >= w-1);
}

void do_case() {
    scanf("%i %i", &s, &w);

    ss.clear();
    for(int i = 0; i < s; ++i) {
        int v;
        scanf("%i", &v);
        ss.push_back(v);
    }
    sort(ss.rbegin(), ss.rend());

    ws.clear();
    for(int i = 0; i < w; ++i) {
        int v;
        scanf("%i", &v);
        ws.push_back(v);
    }
    sort(ws.rbegin(), ws.rend());

    if(ws[0] > ss[0]) {
        printf("impossible\n");
        return;
    }

    int min = 0, max = w;

    while(min != max) {
        int a = (min+max)/2;

        if(check(a)) {
            max = a;
        }
        else {
            min = a+1;
        }
    }

    printf("%i\n", min*3-1);

}

int main() {
    int t;
    scanf("%i", &t);

    while (t--) {
        do_case();
    }

    return 0;
}
