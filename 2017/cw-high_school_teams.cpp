#include<iostream>
#include<unordered_map>
#include<vector>
#include<cmath>

using namespace std;

pair<int, int> dot(vector<int> &a, vector<int> &s) {
    int d = 0;
    int r = 0;

    for(int i = 0; i < (int) a.size(); ++i) {
        d += (a[i]-1)*s[i];
        if(!(a[i]-1)) r++;
    }

    return make_pair(d, r);
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, K;
        cin >> N >> K;

        vector<int> s1(N/2);
        vector<int> s2(N-N/2);

        for(int &es : s1) cin >> es;
        for(int &es : s2) cin >> es;

        if(N == 1) {
            cout << ((s2[0] ? 0 : 2) + (K ? 1 : 0)) << endl;
            continue;
        }

        vector<int> a1(s1.size(), 0); // assignment (0, 1, 2)

        unordered_map<int, unordered_map<int, int> > m;

        for(int it = 0; it < pow(3, a1.size()); ++it) {

            // for(int ea : a1) {
            //     cout << ea << " ";
            // }
            // cout << endl;

            int d, r;
            tie(d, r) = dot(a1, s1);

            a1[0]++;

            for(int ia = 0; ia+1 < (int) a1.size(); ++ia) {
                if(a1[ia] %= 3) break;
                a1[ia+1]++;
            }

            if(r > K) continue;

            if(m.find(d) == m.end()) {
                m.emplace(d, unordered_map<int, int>{});
            }

            if(m[d].find(r) == m[d].end()) {
                m[d].emplace(r, 0);
            }

            m[d][r]++;
        }

        // for(auto em : m) {
        //     cout << em.first << ": ";
        //     for(auto eem : em.second) {
        //         cout << eem.first << " = " << eem.second << ", ";
        //     }
        //     cout << endl;
        // }

        int c = 0;

        vector<int> a2(s2.size(), 0); // assignment (0, 1, 2)

        for(int it = 0; it < pow(3, a2.size()); ++it) {

            // for(int ea : a1) {
            //     cout << ea << " ";
            // }
            // cout << endl;

            int d, r;
            tie(d, r) = dot(a2, s2);

            a2[0]++;

            for(int ia = 0; ia+1 < (int) a2.size(); ++ia) {
                if(a2[ia] %= 3) break;
                a2[ia+1]++;
            }

            if(r > K) continue;

            // cout << -d << " " << r << " " << (m.find(-d) == m.end() ? "no" : "yes") << endl;

            if(m.find(-d) == m.end()) continue;

            for(pair<int, int> em : m[-d]) {
                // cout << "   " << em.first << " " << em.second << endl;
                if((em.first + r) <= K) c += em.second;
            }
        }

        cout << c << endl;
    }

    return 0;
}
