#include<iostream>
#include<vector>
#include<queue>
#include<tuple>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<int> b(N);
        vector<bool> d(N, false);
        priority_queue<pair<int, int> > q;

        cin >> b[0];

        for(int ib = 1; ib < N; ++ib) {
            int tb;
            cin >> tb;

            b[ib] = min(b[(ib-1)/2]-1, tb);

            if(ib > (N-3)/2) {
                q.emplace(-b[ib], ib);
            }
        }

        int t = 0;

        while(q.size()) {
            int ib, tb;
            tie(tb, ib) = q.top();

            if(-tb <= t) break;

            d[ib] = true;

            if(ib && d[ib+ib%2-(ib+1)%2]) {
                q.emplace(-b[(ib-1)/2], (ib-1)/2);
            }

            q.pop();
            t++;
        }

        cout << (q.size() ? "no" : "yes") << endl;

    }
}
