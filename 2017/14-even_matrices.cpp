#include<iostream>
#include<vector>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        vector<vector<int> > s(N, vector<int>(N+1, 0));

        for(int y = 0; y < N; ++y) {
            int v, p = 0;

            for(int x = 0; x < N; ++x) {
                cin >> v;
                p += v;
                s[y][x+1] = p;
            }
        }

        int result = 0;

        for(int x1 = 0; x1 < N; ++x1) {
            for(int x2 = x1; x2 < N; ++x2) {
                int e = 0, o = 0, tmp;

                for(int y = 0; y < N; ++y) {

                    if((s[y][x2+1]-s[y][x1])%2) {
                        tmp = e;
                        e = o;
                        o = tmp+1;
                    } else {
                        e++;
                    }

                    result += e;
                }
            }
        }

        cout << result << endl;

    }

    return 0;
}
