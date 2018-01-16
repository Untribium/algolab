#include<iostream>
#include<vector>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        uint N, M, R, B;
        cin >> N >> M;
        cin >> R >> B;

        R--; B--;

        vector<vector<int> > c(N, vector<int>(0));
        vector<int> b(N, 100000);
        vector<int> w(N, 0);

        while(M--) {
            int u, v;
            cin >> u >> v;

            c[u-1].push_back(v-1);
        }

        b[N-1] = 0; w[N-1] = 0;

        for(int in = N-2; in >= 0; --in) {
            for(int ec : c[in]) {
                b[in] = min(b[in], w[ec]+1);
                w[in] = max(w[in], b[ec]+1);
            }
        }

        if(b[R] == b[B]) {
            cout << (b[B]+1)%2 << endl; continue;
        } else {
            cout << (b[B] < b[R]) << endl;
        }

    }

    return 0;
}
