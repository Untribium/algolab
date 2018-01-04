#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N, Q;
        cin >> N >> Q;

        vector<vector<int> > s(N, vector<int>(1, 0));
        vector<long long> a(N, 0);

        unordered_map<string, int> m;
        vector<string> z(N);

        for(int is = 0; is < N; ++is) {
            cin >> z[is] >> a[is];
            m.emplace(z[is], is);

            s[is][0] = is;
        }

        for(int in = 0; in < N-1; ++in) {
            string o, p;
            cin >> o >> p;
            s[m[o]][0] = m[p];
        }

        int c = 1;
        int l = 0;
        while(c < N) {
            for(int is = 0; is < N; ++is) {
                s[is].push_back(s[s[is][l]][l]);
            }

            c *= 2;
            l += 1;
        }

        l++;

        while(Q--) {
            string n;
            long long b;

            cin >> n >> b;

            int q = m[n];

            while(s[q][0] != q && a[s[q][0]] <= b) {

                int ll = 1, lu = l-1;

                while(ll != lu) {
                    if(a[s[q][(ll+lu)/2]] < b) {
                        ll = (ll+lu)/2+1;
                    } else {
                        lu = (ll+lu)/2;
                    }
                }

                q = s[q][ll-1];
            }

            cout << z[q] << " ";
        }

        cout << endl;
    }
}
