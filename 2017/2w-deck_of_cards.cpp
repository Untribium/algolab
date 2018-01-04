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

        vector<int> v(N);

        cin >> v[0];

        int l = 0, r = 0, s = v[0];

        int bl = 0, br = 0, b = abs(K-s);

        while(true) {

            if(s < K || l == r) {
                r++;
                if(r >= N) {
                    break;
                }
                cin >> v[r];
                s += v[r];
            } else {
                s -= v[l];
                l++;
            }

            if(abs(K-s) < b) {
                b = abs(K-s);
                bl = l;
                br = r;
            }
        }

        cout << bl << " " << br << endl;
    }
}
