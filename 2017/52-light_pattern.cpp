#include<bits/stdc++.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N, K; uint X;
        cin >> N >> K >> X;

        vector<uint> b(N/K, 0); // blocks

        for(int ib = 0; ib < (int) b.size(); ++ib) {
            for(int ik = 0; ik < K; ++ik) {
                int rb;
                cin >> rb;

                b[ib] += rb << (K-1-ik);
            }
        }

        int f = 0;
        int c = 1;

        for(int ib = (int) b.size()-1; ib >= 0; --ib) {

            int bits = bitset<32>(b[ib] ^ X).count();

            if(c == 0) c = (K-bits < bits ? -1 : +1);

            if(c == -1) bits = K-bits;

            if(K-bits+1 < bits) {
                c = -c;
                f += K-bits+1;
            } else if(K-bits+1 == bits) {
                c = 0;
                f += bits;
            } else {
                f += bits;
            }
        }

        cout << f << endl;
    }

    return 0;
}
