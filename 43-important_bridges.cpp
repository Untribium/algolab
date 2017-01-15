#include<stdio.h>

#include<boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_name_t, int>> Graph;


void do_case(int t) {
    int n, m;
    scanf("%i %i", &n, &m);

    for(int i = 0; i < m; ++i) {
        int e1, e2;
        scanf("%i %i", &e1, &e2);


    }
}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case(t)
    }

    return 0;
}
