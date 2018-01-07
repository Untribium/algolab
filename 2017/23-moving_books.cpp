#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool too_small(vector<int> &s, vector<int> &w, int r) {
    int iw = 0, is = 0;
    while(iw < w.size() && is < s.size()) {
        
        if(s[is] < w[iw]) return true;
        
        iw += r;
        is += 1;
    }
    return iw < w.size();
}

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N, M;
        cin >> N >> M;

        vector<int> s(N, 0), w(M, 0);

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

        int a = ceil(M/N), b = M, r;

        while(a != b) {
            if(too_small(s, w, r = (a+b)/2)) {
                a = r+1;
            } else {
                b = r;
            }
        }

        cout << a*3-1 << endl;
    }
}
