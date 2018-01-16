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

            vector<int> d(R);
            int s = 0;

            for(uint ir = 0; ir < R; ++ir) {

                d[ir] = 0;
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
                        d[ir] += e[ir][S/2+is];
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

        // vector<vector<int> > d2r(1 << (S-S/2), vector<int>(R));
        //
        // for(uint id = 0; id < d2.size(); ++id) {
        //
        //     d2[id].first = 0;
        //     d2[id].second = &d2r[id];
        //
        //     for(uint ir = 0; ir < R; ++ir) {
        //
        //         d2r[id][ir] = b[ir];
        //
        //         for(uint is = 0; is < (S-S/2); ++is) {
        //             if((id >> is) & 1) {
        //                 d2r[id][ir] += e[ir][is];
        //             }
        //         }
        //
        //         d2r[id][ir] = t[ir] - d2r[id][ir];
        //
        //         d2[id].first += d2r[id][ir];
        //     }
        // }
        //
        // sort(d1.begin(), d1.end());
        // sort(d2.begin(), d2.end());
        //
        // uint p1 = 0, p2 = 0, op2 = 0;
        // int s = 100;
        //
        // while(p1 < d1.size()) {
        //
        //     if((p2 >= d2.size() || d1[p1].first < d2[p2].first) && op2) {
        //         p1++;
        //         p2 = op2;
        //         op2 = 0;
        //         continue;
        //     }
        //
        //     if(d1[p1].first > d2[p2].first){
        //         p2++; continue;
        //     }
        //
        //     if(d1[p1].first == d2[p2].first) {
        //         // check
        //         p2++;
        //     }
        //
        //
        // }
    }

    return 0;
}
