#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        uint K, N, Q;
        cin >> K >> N >> Q;

        vector<pair<long long, int> > b(K);

        for(auto &eb : b) {
            long long l, u, d;
            cin >> l >> u;

            eb.first = l;

            d = u-l;
            int k = 0;

            while((1 << (k++))-1 < d);

            eb.second = max(k, 1);
        }

        unordered_map<long long, int> m;

        while(N--) {
            int o = 0;
            long long v = 0;
            for(uint ib = 0; ib < b.size(); ++ib) {
                int c;
                cin >> c;

                v += (c-b[ib].first) << o;
                o += b[ib].second;
            }
            int r;
            cin >> r;
            m.emplace(v, r);
        }

        while(Q--) {
            int o = 0;
            long long v = 0;
            for(uint ib = 0; ib < b.size(); ++ib) {
                int c;
                cin >> c;

                v += (c-b[ib].first) << o;
                o += b[ib].second;
            }

            if(m.find(v) == m.end()) {
                cout << -1 << endl;
            } else {
                cout << m[v] << endl;
            }
        }
    }

    return 0;
}
