#include<iostream>
#include<vector>
#include<map>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        uint S, R;
        cin >> S >> R;

        vector<int> t(R); // brightness target

        for(int &et : t) {
            cin >> et;
        }

        vector<int> b(R, 0); // brightness base
        vector<vector<int> > e(R, vector<int>(S)); // effect

        for(uint is = 0; is < S; ++is) {
            for(uint ir = 0; ir < R; ++ir) {
                int on, off;
                cin >> on >> off;

                b[ir] += on;
                e[ir][is] = off-on;
            }
        }

        int r = 100;

        map<vector<int>, int> m;

        for(int id = 0; id < (1 << S/2); ++id) {

            vector<int> d(R, 0);
            int s = 0;

            for(uint ir = 0; ir < R; ++ir) {

                s = 0;

                for(uint is = 0; is < S/2; ++is) {
                    if((id >> is) & 1) {
                        d[ir] += e[ir][is];
                        s++;
                    }
                }
            }

            if(m.find(d) != m.end()) {
                m[d] = min(m[d], s);
            } else {
                m.emplace(d, s);
            }
        }

        for(int id = 0; id < (1 << (S-S/2)); ++id) {

            vector<int> d(R);
            int s = 0;

            for(uint ir = 0; ir < R; ++ir) {

                d[ir] = t[ir] - b[ir];
                s = 0;

                for(uint is = 0; is < (S-S/2); ++is) {
                    if((id >> is) & 1) {
                        d[ir] -= e[ir][S/2+is];
                        s++;
                    }
                }
            }

            if(m.find(d) != m.end()) {
                r = min(r, m[d]+s);
            }
        }

        if(r < 100) {
            cout << r << endl;
        } else {
            cout << "impossible" << endl;
        }
    }

    return 0;
}
