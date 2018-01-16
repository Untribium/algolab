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

        map<vector<int>, int> m1;

        for(int id = 0; id < (1 << S/2); ++id) {

            vector<int> d(R);
            int s = 0;

            for(uint ir = 0; ir < R; ++ir) {

                d[ir] = b[ir] - t[ir];
                s = 0;

                for(uint is = 0; is < S/2; ++is) {
                    if((id >> is) & 1) {
                        d[ir] += e[ir][is];
                        s++; // wasteful, oh well
                    }
                }
            }

            if(m1.find(d) != m1.end()) {
                m1[d] = min(m1[d], s);
            } else {
                m1.emplace(d, s);
            }
        }

        map<vector<int>, int> m2;

        for(int id = 0; id < (1 << (S-S/2)); ++id) {

            vector<int> d(R);
            int s = 0;

            for(uint ir = 0; ir < R; ++ir) {

                d[ir] = b[ir] - t[ir];
                s = 0;

                for(uint is = 0; is < (S-S/2); ++is) {
                    if((id >> is) & 1) {
                        d[ir] += e[ir][is];
                        s++; // wasteful, oh well
                    }
                }
            }

            if(m2.find(d) != m2.end()) {
                m2[d] = min(m2[d], s);
            } else {
                m2.emplace(d, s);
            }
        }

        int s = 100;

        for(auto em1 : m1) {
            if(m2.find(em1.first) != m2.end()) {
                s = min(s, em1.second+m2[em1.first]);
            }
        }

        if(s < 100) {
            cout << s << endl;
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
}
