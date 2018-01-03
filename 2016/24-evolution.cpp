#include<vector>
#include<stdio.h>
#include<unordered_map>
#include<algorithm>

using namespace std;

unordered_map<string, int> indices;
vector<int> species;
vector<int> ancestor;
vector<char*> names;

void do_case() {

    int n, q;
    scanf("%i %i", &n, &q);

    species.clear();
    species.assign(n+1, 0);

    ancestor.clear();
    ancestor.assign(n+1, 0);

    names.clear();
    names.resize(n+1);

    for(int i = 1; i <= n; ++i) {
        char* name = new char[11];
        int age;

        scanf("%s %i", name, &age);

        indices.insert({string(name), i});
        names[i] = name;
        species[i]= age;
    }

    for(int i = 0; i < n-1; ++i) {
        char n1[11], n2[11];

        scanf("%s %s", &n1, &n2);

        ancestor[indices[string(n1)]] = indices[string(n2)];
    }

    for(int i = 0; i < q; ++i) {
        char name[11];
        int age;

        scanf("%s %i", &name, &age);

        int last_i = indices[string(name)];

        while(ancestor[last_i] && species[ancestor[last_i]] <= age) {
            last_i = ancestor[last_i];
        }

        printf("%s ", names[last_i]);
    }

    printf("\n");
}

int main() {
    int t;
    scanf("%i", &t);

    while (t--) {
        do_case();
    }

    return 0;
}
