#include <bits/stdc++.h>

using namespace std;

long long sum;

pair<array<long long,4>, long long> dot(vector<char> &a, vector<int> &l) {

    vector<vector<long long> > s(4, vector<long long>(3, 0));
    array<long long, 4> r;

    for(long long ia = 0; ia < (long long) a.size(); ++ia) {
        s[a[ia]][0] += l[ia]; // total length
        if(s[a[ia]][0] > sum/4) return make_pair(r, 0LL);
        s[a[ia]][1] ^= (ia << (4*s[a[ia]][2]));
        s[a[ia]][2] += 1;     // number of planks
    }

    sort(s.begin(), s.end());

    long long c = 0, o = 0; // composite, offset

    for(int is = 0; is < (int) s.size(); ++is) {
        c ^= (s[is][1] << o);
        o += (s[is][2]*4);
        c ^= (15 << o); // add 1111 between sides for uniqueness
        o += 4;
        r[is] = s[is][0];
    }

    return make_pair(r, c);
}

char msb(vector<char> &a) {
    for(int ia = a.size()-1; ia >= 0; --ia) {
        if(a[ia]) return a[ia];
    }
    return 0;
}

bool valid(vector<char> &a) {
    vector<bool> f(4, false);
    int top = 0;

    for(int ia = a.size()-1; ia >= 0; --ia) {
        if(!f[a[ia]] && top > a[ia]){
            return false;
        }
        f[a[ia]] = true;
        top = max(top, (int) a[ia]);
    }

    return true;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<int> l1(N/2), l2(N-N/2);
        long long max = 0;
        sum = 0;

        for(int &el : l1) {
            cin >> el;
            sum += el;
            max = (el > max ? el : max);
        }

        for(int &el : l2) {
            cin >> el;
            sum += el;
            max = (el > max ? el : max);
        }

        if(N < 4 || sum % 4 || max*4 > sum) {
            cout << 0 << endl;
            continue;
        }

        vector<char> a1(l1.size(), 0), a2(l2.size(), 0);
        map<array<long long,4>, int> m;
        set<long long> s;

        for(int i = 0; i < pow(4, a1.size()-1); ++i) {

            if(msb(a1) > 1 || !valid(a1)){
                for(char &ea : a1) if((ea += 1) %= 4) break;
                continue;
            }

            array<long long,4> d;
            long long u;
            tie(d, u) = dot(a1, l1);

            for(char &ea : a1) if((ea += 1) %= 4) break;

            if(!u) continue;

            if(s.insert(u).second) {
                m[d]++;
            }
        }

        s.clear();
        long long total = 0;

        for(int i = 0; i < pow(4, a2.size()-1); ++i) {

            if(msb(a2) > 1 || !valid(a2)){
                for(char &ea : a2) if((ea += 1) %= 4) break;
                continue;
            }

            array<long long,4> d;
            long long u;
            tie(d, u) = dot(a2, l2);

            for(char &ea : a2) if((ea += 1) %= 4) break;

            if(!u) continue;

            array<long long,4> r{sum/4-d[3], sum/4-d[2], sum/4-d[1], sum/4-d[0]};

            if(s.insert(u).second && m.find(r) != m.end()) {

                int count = 0, val = 0, add = m[r];

                for(int k = 0; k < 4; ++k) {
                    if(d[k] && r[3-k]) {

                        if(val != d[k]) count = 0;

                        val = d[k];
                        add *= ++count;
                    }
                }

                total += add;
            }
        }

        cout << total << endl;
    }

    return 0;
}
