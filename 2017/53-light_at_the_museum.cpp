#include<iostream>
#include<vector>

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

        vector<int> d(1 << S/2, 0);
        vector<vector<int> > dr(R, vector<int>(R));

        for(uint id = 0; id < d.size(); ++id) {

            for(uint ir = 0; ir < R; ++ir) {

                dr[id][ir] = b[ir];

                for(uint is = 0; is < S/2; ++is) {
                    if((id >> is) & 1) {
                        dr[id][ir] += e[ir][is];
                    }
                }

                dr[id][ir] -= t[ir];

                d[ir] += dr[id][ir];
            }
        }

        


    }
}
