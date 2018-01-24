#include<iostream>
#include<unordered_map>

using namespace std;

typedef __uint128_t int128;

pair<vector<long long>, int128> dot(vector<char> &a, vector<int> &l) {

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        int N;
        cin >> N;

        vector<int> l1(N/2), l2(N-N/2);
        long long sum = 0, max = 0

        for(int &el : l1) {
            cin >> el;
            sum += el;
            max = (el > max ? el : max);
        }

        for(int &el : l1) {
            cin >> el;
            sum += el;
            max = (el > max ? el : max);
        }

        if(N < 4 || sum % 4 || max*4 > sum) continue;

        vector<char> a1(l1.size(), 0), a2(s2.size(), 0);

        for(int i = 0; i < pow(4, a1.size()); ++i) {
            pair<long long,
        }
    }

    return 0;

    unordered_map<__uint128_t, int> m;
}
