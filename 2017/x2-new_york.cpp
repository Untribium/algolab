#include<bits/stdc++.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, M, K;
        cin >> N >> M >> K;

        int B = 0, m = M-1, ib;
        for(ib = 1; m > 0; ++ib, m >>= 1) {
            if(m & 1) B = ib;
        }

        vector<vector<int> > p(N+1, vector<int>(B, 0));
        vector<vector<pair<int, int> > > temp(N+1, vector<pair<int, int> >(B+1, make_pair(0, 0)));

        for(int in = 1; in <= N; ++in) {
            int t;
            cin >> t;
            temp[in][0] = make_pair(t, t);
            cout << temp[in][0].first << "/" << temp[in][0].second << " ";
        }
        cout << endl;

        for(int in = 0; in < N-1; ++in) {
            int from, to;
            cin >> from >> to;
            p[to+1][0] = from+1;
        }

        for(int ib = 1; ib <= B; ++ib) {
            for(int in = 1; in <= N; ++in) {
                int pp = p[in][ib-1];
                if(pp == 0) {cout << "-/- "; continue; }
                p[in][ib] = p[pp][ib-1];
                temp[in][ib].first = min(temp[in][ib-1].first, temp[pp][ib-1].first);
                temp[in][ib].second = max(temp[in][ib-1].second, temp[pp][ib-1].second);
                cout << temp[in][ib].first << "/" << temp[in][ib].second << " ";
            }
            cout << endl;
        }

        set<int> r;
        for(int in = 1; in <= N; ++in) {
            int cmin = INT_MAX, cmax = INT_MIN, c = in;
            for(m = M-1, ib = 0; m > 0; m >>= 1, ++ib) {
                if(!c) break;
                if((m & 1) == 0) continue;
                cmin = min(cmin, temp[c][ib+1].first);
                cmax = max(cmax, temp[c][ib+1].second);
                c = p[c][ib];
            }
            if(!m && c && cmax-cmin <= K) r.insert(c-1);
        }

        if(r.empty()) { cout << "Abort mission" << endl; continue; }

        for(int er : r) cout << er << " ";
        cout << endl;
    }

    return 0;
}
