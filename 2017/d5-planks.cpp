#include<iostream>
#include<set>
#include<map>
#include<cmath>
#include<vector>
#include<bitset>
#include<algorithm>

using namespace std;

pair<vector<long long>, long long> dot(vector<char> &a, vector<int> &l) {

    vector<vector<long long> > s(4, vector<long long>(3, 0));

    for(int ia = 0; ia < (int) a.size(); ++ia) {
        s[a[ia]][0] += l[ia]; // total length
        s[a[ia]][1] ^= (ia << (4*s[a[ia]][2]));
        s[a[ia]][2] += 1;     // number of planks
    }

    sort(s.begin(), s.end());

    long long c = 0, o = 0; // composite, offset
    vector<long long> r(4);

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
    char msb = 0;

    for(int ia = a.size()-1; ia >= 0; --ia) {
        if(a[ia]){
            msb = a[ia];
            break;
        }
    }

    return msb;
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
        long long sum = 0, max = 0;

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
        map<vector<long long>, int> m;
        set<long long> s;

        for(int i = 0; i < pow(4, a1.size()-1); ++i) {

            // if(msb(a1) > 1){
            //     for(char &ea : a1) if((ea += 1) %= 4) break;
            //     continue;
            // }

            if(!valid(a1)){
                for(char &ea : a1) if((ea += 1) %= 4) break;
                continue;
            }

            vector<long long> d;
            long long u;
            tie(d, u) = dot(a1, l1);

            for(char &ea : a1) if((ea += 1) %= 4) break;

            if(d[3]*4 > sum) continue;

            if(s.insert(u).second) {
                m[d]++;
            }
        }

        s.clear();
        long long total = 0;

        for(int i = 0; i < pow(4, a2.size()-1); ++i) {

            // if(msb(a2) > 1){
            //     for(char &ea : a2) if((ea += 1) %= 4) break;
            //     continue;
            // }

            if(!valid(a2)){
                for(char &ea : a2) if((ea += 1) %= 4) break;
                continue;
            }

            vector<long long> d;
            long long u;
            tie(d, u) = dot(a2, l2);

            for(char &ea : a2) if((ea += 1) %= 4) break;

            if(d[3]*4 > sum) continue;

            vector<long long> r{sum/4-d[3], sum/4-d[2], sum/4-d[1], sum/4-d[0]};

            if(s.insert(u).second && m.find(r) != m.end()) {
                total += m[r];
            }
        }

        cout << total << endl;
    }

    return 0;
}
