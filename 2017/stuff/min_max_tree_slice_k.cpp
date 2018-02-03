#include<bits/stdc++.h>

using namespace std;

struct Node {
    int num;
    int temp;               // temperature
    int depth;              // depth
    pair<int, int> frun;    // min max forwards
    pair<int, int> brun;    // min max backwards
    Node *parent;           // parent
    Node *back;             // back pointer
    Node *child;            // current dfs child
    vector<Node*> routes;   // children
};

int N, M, K;

void dfs(Node &n, Node *root) {

    if(n.parent) {                       // if n has a parent
        n.depth = n.parent->depth+1;     // take its depth and add one
    } else {                             // otherwise
        n.depth = 0;                     // initialize depth to 0
    }

    if(n.depth % M == 0) {                                  // if start of new block
        n.frun = make_pair(n.temp, n.temp);                 // then reset
    } else {                                                // otherwise
        n.frun.first = min(n.parent->frun.first, n.temp);   // update forwards run min
        n.frun.second = max(n.parent->frun.second, n.temp); // and max
    }

    if(n.parent && n.parent->back) {     // if n has a parent and the parent has a back pointer
        n.back = n.parent->back->child;  // update my back pointer to the child currently in the dfs
    } else if(n.depth == M-1) {          // otherwise check if deep enough to start
        n.back = root;                   // if so, initialize back pointer to root
    }

    n.brun = make_pair(n.temp, n.temp);  // initialize backwards run to own temp value

    for(Node *c : n.routes) {            // iterate over children
        n.child = c;                     // set current dfs child (so we know where to move the back pointer later)
        dfs(*c, root);                   // recurse

        if(n.depth % M == M-1) continue; // if at end of block (start for bw run), ignore values from children

        n.brun.first = min(c->brun.first, n.brun.first);    // update backwards run min
        n.brun.second = max(c->brun.second, n.brun.second); // and max
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while(T--) {

        cin >> N >> M >> K;

        vector<Node> n(N);

        for(int in = 0; in < N; ++in) {
            cin >> n[in].temp;
            n[in].num = in;
        }

        for(int in = 0; in < N-1; in++) {
            int u, v;
            cin >> u >> v;

            n[u].routes.push_back(&n[v]);
            n[v].parent = &n[u];
        }

        dfs(n[0], &n[0]);

        set<int> r;

        for(int in = 0; in < N; ++in) {

            cout << "---" << endl;
            cout << in << endl;
            cout << n[in].frun.first << " " << n[in].frun.second << endl;
            cout << n[in].brun.first << " " << n[in].brun.second << endl;

            if(n[in].back) {

                int mi = min(n[in].back->brun.first,  n[in].frun.first);
                int ma = max(n[in].back->brun.second, n[in].frun.second);

                if(ma-mi <= K) r.insert(n[in].back->num);
            }
        }

        if(!r.size()) { cout << "Abort mission" << endl; continue; }

        for(int er : r) {
            cout << er << " ";
        }
        cout << endl;
    }

    return 0;
}
