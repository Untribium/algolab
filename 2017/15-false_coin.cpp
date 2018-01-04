#include<iostream>
#include<vector>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N, K;

        cin >> N >> K;

        vector<bool> c(N, true);
        vector<char> w(N, 0);

        while(K--) {
            int P;
            cin >> P;

            vector<char> u(N, 0);
            int i;

            for(int ip = 0; ip < 2*P; ++ip) {
                cin >> i;
                u[i-1] = (ip<P ? -1 : +1);
            }

            char r;
            cin >> r;

            if(r == '=') {
                for(int ic = 0; ic < N; ++ic) {
                    if(u[ic]) {
                        c[ic] = false;
                    }
                }
            } else {
                r = (r == '<' ? +1 : -1);

                for(int ic = 0; ic < N; ++ic) {
                    if(!u[ic]) {
                        c[ic] = false;
                    } else {
                        char rp = u[ic]*r;
                        if(w[ic] && w[ic] != rp) {
                            c[ic] = false;
                        } else {
                            w[ic] = rp;
                        }
                    }
                }
            }
        }

        int o = 0, v = 0;

        for(int ic = 0; ic < N; ++ic) {
            if(c[ic]) {
                v = ic+1;
                o++;
            }
        }

        cout << (o == 1 ? v : 0) << endl;
    }

    return 0;
}
