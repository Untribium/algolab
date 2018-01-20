#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

unordered_map<long long, int > m;

long long vec_to_ll(const vector<int> &t) {
    long long o = 0;
    for(int it = 0; it < (int) t.size(); ++it) {
        o += ((long long) t[it] << it*11);
    }
    return o;
}

int points(int k) {
    return (--k) ? 1 << --k : 0;
}

int take(const vector<vector<int> > &s, const vector<int> &t) {

    if(m.find(vec_to_ll(t)) != m.end()) return m[vec_to_ll(t)]; // memo

    int v = 0;

    for(int bm = 1; bm < (1 << s.size()); ++bm) {

        int c = 0, k = 0, is = 0;
        vector<int> l(t);

        for(is = 0; is < (int) s.size(); ++is) {

            if(bm & (1 << is)) {

                if(l[is]-- <= 0) break;
                if(c && c != s[is][t[is]-1]) break;

                c = s[is][t[is]-1];
                k++;
            }
        }

        if(is < (int) s.size()) continue; // broke

        v = max(v, points(k)+take(s, l));
    }

    m.emplace(vec_to_ll(t), v);

    return v;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<vector<int> > s(N, vector<int>(0)); // stacks
        vector<int> t(N); // top

        m.clear();
        m.emplace(vec_to_ll(vector<int>(N, 0)), 0); // escape condition

        for(int is = 0; is < (int) s.size(); ++is) {
            cin >> t[is];
            s[is].assign(t[is], 0);
        }

        for(auto &es : s) {
            for(int &ees : es) {
                cin >> ees;
            }
        }

        cout << take(s, t) << endl;
    }
    
    return 0;
}
