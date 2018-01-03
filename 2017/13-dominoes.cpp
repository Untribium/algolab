#include<iostream>

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    while(T--) {
        int N;
        cin >> N;

        int i = 1, p = 2, v; // init to 2 so first domino falls

        while(N--) {
            cin >> v;

            if(p > i) {
                p = max(p, (i++)+v);
                continue;
            }

            break;

        }

        while(N-- > 0) {
            cin >> v;
        }

        cout << i-1 << endl;
    }

    return 0;
}
