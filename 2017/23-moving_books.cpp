#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T, N, M;

bool too_small(vector<int> &s, vector<int> &w, int r) {
    int iw = 0;
    for(es : s) {

        if(es < w[iw]) return true;

        iw += r;

        if(iw >= M) return false;
    }

    return true;
}

int main() {

    ios_base::sync_with_stdio(false);

    cin >> T;

    while(T--) {
        cin >> N >> M;

        vector<int> s(N, 0);
        vector<int> w(M, 0);

        for(int &es : s) {
            cin >> es;
        }

        for(int &ew : w) {
            cin >> ew;
        }

        sort(s.begin(), s.end(), greater<int>());
        sort(w.begin(), w.end(), greater<int>());

        if(s[0] < w[0]) {
            cout << "impossible" << endl;
            continue;
        }

        int a = 1, b = 1;

        while(too_small(s, w, b)) {
            b *= 2;
        }

        while(a != b) {
            if(too_small(s, w, (a+b)/2)) {
                a = (a+b)/2+1;
            } else {
                b = (a+b)/2;
            }
        }

        cout << (a-1)*3+2 << endl;
    }
}
