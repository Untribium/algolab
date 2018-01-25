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

    for(long long ia = 0; ia < (long long) a.size(); ++ia) {
        s[a[ia]][0] += l[ia]; // total length
        s[a[ia]][1] ^= (ia << (4*s[a[ia]][2]));
        s[a[ia]][2] += 1;     // number of planks
    }

    sort(s.begin(), s.end());

    long long c = 0, o = 0; // composite, offset
    vector<long long> r(4);

    for(int is = 0; is < (int) s.size(); ++is) {
        // cout << s[is][0] << " " << bitset<40>(s[is][1]) << " " << s[is][2] << " " << endl;
        c ^= (s[is][1] << o);
        o += (s[is][2]*4);
        c ^= (15 << o); // add 1111 between sides for uniqueness
        o += 4;
        r[is] = s[is][0];
    }

    // cout << bitset<56>(c) << endl;

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

            if(msb(a1) > 1){
                for(char &ea : a1) if((ea += 1) %= 4) break;
                continue;
            }

            if(!valid(a1)){
                for(char &ea : a1) if((ea += 1) %= 4) break;
                continue;
            }

            // cout << "run" << endl;

            vector<long long> d;
            long long u;
            tie(d, u) = dot(a1, l1);

            for(char &ea : a1) if((ea += 1) %= 4) break;

            if(d[3]*4 > sum) continue;

            if(s.insert(u).second) {
                // cout << "insert" << endl;
                m[d]++;
            }
        }

        // for(auto em : m) {
        //     for(long long eem : em.first) {
        //         cout << eem;
        //     }
        //     cout << ": " << em.second << endl;
        // }

        s.clear();
        long long total = 0;

        for(int i = 0; i < pow(4, a2.size()-1); ++i) {

            if(msb(a2) > 1){
                for(char &ea : a2) if((ea += 1) %= 4) break;
                continue;
            }

            if(!valid(a2)){
                for(char &ea : a2) if((ea += 1) %= 4) break;
                continue;
            }

            // for(long long ea : a2) {
            //     cout << ea;
            // }
            // cout << " i" << endl;

            vector<long long> d;
            long long u;
            tie(d, u) = dot(a2, l2);

            for(char &ea : a2) if((ea += 1) %= 4) break;

            vector<long long> r{sum/4-d[3], sum/4-d[2], sum/4-d[1], sum/4-d[0]};

            // for(long long er : r) {
            //     cout << er;
            // }
            // cout << ": " << endl << bitset<56>(u) << endl;

            if(d[3]*4 > sum) continue;

            if(s.insert(u).second && m.find(r) != m.end()) {
                // cout << "add" << endl;

                int add = 1;
                int count = 0;
                int val = 0;

                for(int k = 0; k < 4; ++k) {
                    if(d[k] && d[k] < sum/4) {
                        if(val != d[k]) {
                            val = d[k];
                            count = 1;
                        } else {
                            count++;
                        }
                        add *= count;
                    }
                }

                total += m[r]*add;
            }
        }

        cout << total << endl;
    }

    return 0;
}
