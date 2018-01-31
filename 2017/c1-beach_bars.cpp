#include<bits/stdc++.h>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<int> p(N);

        for(int ip = 0; ip < N; ++ip) {
            cin >> p[ip];
        }

        sort(p.begin(), p.end());

        int l = 0, r = 0, d = 0, c = 1;
        pair<int, int> b = make_pair(1, 0);
        vector<int> bs;
        bs.push_back(p[0]);

        while(true) {
            if(l >= r || d <= 200) {
                if(++r >= N) break;
                d += p[r]-p[r-1];
                c++;
            } else {
                c--;
                d -= p[l+1]-p[l];
                l++;
            }

            if(d > 200) continue;

            pair<int, int> h = make_pair(c, -((d+1)/2));

            if(h < b) continue;

            if(h > b) {
                bs.clear();
                b = h;
            }

            bs.push_back(p[l]+d/2);
            if(d%2) bs.push_back(p[l]+d/2+1);
        }

        cout << b.first << " " << -b.second << endl;

        for(int ebs : bs) cout << ebs << " ";
        cout << endl;
    }

    return 0;
}
