#include<iostream>
#include<vector>
#include<bitset>

using namespace std;

vector<short> c(1 << 16);
vector<bool> v(1 << 16);

void bitcounts() {
    for(int ic = 0; ic < (int) c.size(); ++ic) {
        c[ic] = bitset<16>((short) ic).count();

        int i = 0;
        bool f = false;

        for(i = 0; i < 16; ++i) {
            if((ic & (1 << i)) == 0) {
                if(f) break;
            } else {
                f = !f;
            }
        }

        v[ic] = !f && i == 16;
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    bitcounts();

    int T;
    cin >> T;

    while(T--) {

        int H, W;
        cin >> H >> W;

        vector<short> b(H, 0);

        for(int ih = 0; ih < H; ++ih) {
            int v;
            cin >> v; // drop first column

            for(int iw = 0; iw < W-2; ++iw) {
                cin >> v;
                if(!v) {
                    b[ih] += (1 << iw);
                }
            }

            if(W > 1) cin >> v; // drop last column
        }

        if(W < 4 || H < 4) {
            cout << 0 << endl;
            continue;
        }

        W -= 2;

        vector<short> l(1 << W, 0), t(1 << W, 0);
        short m = 0;

        for(int ih = 2; ih < H-1; ++ih) {
            t[0] = m;

            for(int i = 1; i < (1 << W); ++i) {
                t[i] = 0;

                for(int j = 0; j < W; ++j) {
                    if(i & (1 << j)) {
                        t[i] = max(t[i], t[i ^ (1 << j)]);
                    }
                }

                if(v[i] && !(i & b[ih]) && !(i & b[ih-1])) {
                    short z = l[((1 << W)-1) ^ i]+c[i]/2;
                    t[i] = t[i] < z ? z : t[i];
                }

                m = max(m, t[i]);
            }

            l = t;
        }

        cout << m << endl;

    }

    return 0;
}
