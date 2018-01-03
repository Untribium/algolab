#include<vector>
#include<stdio.h>
#include<unordered_map>
#include<algorithm>
#include<iostream>

using namespace std;

struct Species {
    char* name;
    int age;
    int depth;
    int left;
    int right;
    Species* p;
    vector<Species*> c;
};

unordered_map<string, Species*> map;
vector<Species> species;

vector<vector<Species*>> intervals;

int index;

void dfs(Species* node, int d) {
    node->depth = d;
    node->left = index;
    index++;

    for(Species* c : node->c) {
        dfs(c, d+1);
    }

    node->right = index;
    index++;

    if(intervals.size() < d+1) {
        intervals.resize(d+1);
    }
    intervals[d].push_back(node);
};

void do_case() {

    int n, q;
    scanf("%i %i", &n, &q);

    map.clear();
    species.clear();
    species.resize(n);

    for(int i = 0; i < n; ++i) {
        char* name = new char[11];
        int age;

        scanf("%s %i", name, &age);

        species[i].name = name;
        species[i].age = age;

        map.insert({string(name), &species[i]});
    }

    for(int i = 0; i < n-1; ++i) {
        char n1[11], n2[11];

        scanf("%s %s", n1, n2);

        Species* parent = map[string(n2)];
        Species* child = map[string(n1)];

        child->p = parent;
        parent->c.push_back(child);
    }

    Species* root = &species[0];

    while(root->p) {
        root = root->p;
    }

    intervals.clear();

    index = 0;

    dfs(root, 0);

    for(int i = 0; i < q; ++i) {
        char name[11];
        int age;

        scanf("%s %i", &name, &age);

        Species* target = map[string(name)];

        int d_min = 0, d_max = target->depth;
        int i_min, i_max;

        while(true) {
            int d_cur = (d_max+d_min)/2;

            i_min = 0;
            i_max = intervals[d_cur].size()-1;

            while(i_min != i_max) {
                int i_cur = (i_max+i_min)/2;

                if(target->right <= intervals[d_cur][i_cur]->right) {
                    i_max = i_cur;
                }
                else {
                    i_min = i_cur+1;
                }
            }

            if(d_min == d_max) {
                break;
            }

            if(intervals[d_cur][i_min]->age > age) {
                d_min = d_cur+1;
            }
            else {
                d_max = d_cur;
            }
        }

        printf("%s ", intervals[d_min][i_min]->name);
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
