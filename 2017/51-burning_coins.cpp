#include<iostream>
#include<vector>

using namespace std;

vector<int> v;
vector<vector<int> > m;

int take(int l, int r) {

    if(l > r) return 0;
    if(l == r) return v[l];

    if(!m[l][r]) { // max(min(xx--, x--x)+l, min(--xx, x--x)+r);
        m[l][r] = max(v[l]+min(take(l+2, r), take(l+1, r-1)), v[r]+min(take(l+1, r-1), take(l, r-2)));
    }

    return m[l][r];
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        v.clear();
        v.assign(N, 0);

        for(auto em : m) em.clear();
        m.clear();
        m.assign(N, vector<int>(N, 0));

        for(int &ev : v) cin >> ev;

        cout << take(0, N-1) << endl;
    }
}
