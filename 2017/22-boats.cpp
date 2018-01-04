#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        vector<pair<int, int> > b(N, make_pair(0, 0));

        for(int ib = 0; ib < N; ++ib){
            cin >> b[ib].second >> b[ib].first;
        }

        sort(b.begin(), b.end());

        int p = b[0].first, o = -10000000, c = 1;

        for(int ib = 1; ib < N; ++ib) {
            if(b[ib].first >= p) {
                o = p;
                p = max(o+b[ib].second, b[ib].first);
                c++;
            } else {
                p = min(p, max(o+b[ib].second, b[ib].first));
            }
        }

        cout << c << endl;
    }
}
