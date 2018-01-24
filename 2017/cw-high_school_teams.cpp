#include<iostream>
#include<unordered_map>
#include<vector>
#include<cmath>

using namespace std;

pair<int, int> dot(vector<char> &a, vector<int> &s) {
    int d = 0, r = 0;

    for(int i = 0; i < (int) a.size(); ++i) {
        d += (a[i]-1) * s[i];
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

        vector<char> a1(s1.size(), 0); // assignment (0, 1=ref, 2)

        unordered_map<int, unordered_map<char, int> > m;

        for(int it = 0; it < pow(3, a1.size()); ++it) {

            int d, r;
            tie(d, r) = dot(a1, s1);

            for(char &ea : a1) {
                if((ea += 1) %= 3) break;
            }

            if(r > K) continue;

            m[d][r]++;
        }

        long long c = 0;
        vector<char> a2(s2.size(), 0); // assignment (0, 1=ref, 2)

        for(int it = 0; it < pow(3, a2.size()); ++it) {

            int d, r;
            tie(d, r) = dot(a2, s2);

            for(char &ea : a2) {
                if((ea += 1) %= 3) break;
            }

            if(r > K) continue;

            if(m.find(-d) == m.end()) continue;

            for(pair<int, int> em : m[-d]) {
                if((em.first + r) <= K) c += em.second;
            }
        }

        cout << c << endl;
    }

    return 0;
}
