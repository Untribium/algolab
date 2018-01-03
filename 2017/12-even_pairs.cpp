#include<iostream>

using namespace std;

int main() {
    int T;
    cin >> T;

    while(T--) {
        int n;
        cin >> n;

        int e = 0, o = 0, t = 0, v, tmp; //even, odd, sum

        while(n--) {
            cin >> v;

            if(!v) {
                e++;
            } else {
                tmp = e;
                e = o;
                o = tmp+1;
            }

            t += e;
        }

        cout << t << endl;
    }
}
