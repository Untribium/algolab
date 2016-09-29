// #include<stdio.h>
#include<iostream>
#include<string.h>
#include<unordered_map>

using namespace std;

unordered_map<string, int> s;
unordered_map<string, string> a;

void do_case() {
    int n, q;
    // scanf("%i %i\n", &n, &q);
    cin >> n;
    cin >> q;

    s.clear();
    a.clear();

    for(int i = 0; i < n; ++i) {
        // char name[11];
        string name;
        int age;

        // scanf("%s %i", &name, &age);

        cin >> name;
        cin >> age;

        s.insert({name, age});
    }

    for(int i = 0; i < n-1; ++i) {
        // char c[11], p[11];
        string c, p;

        cin >> c;
        cin >> p;

        // scanf("%s %s", &c, &p);

        a.insert({c, p});
    }

    for(int i = 0; i < q; ++i) {
        // char* last = new char[11];
        string last;
        int age;

        // scanf("%s %i", last, &age);
        cin >> last;
        cin >> age;

        while(a.count(last) && s[a[last]] <= age) {
            last = a[last];
        }

        // printf("%s ", last);
        cout << last << " ";
    }

    // printf("\n");
    cout << "\n";

}

int main() {

    std::ios_base::sync_with_stdio(false);

    int t;
    // scanf("%i", &t);
    cin >> t;

    while (t--) {
        do_case();
    }

    return 0;
}
