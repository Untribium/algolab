#include<stdio.h>
#include<vector>
#include<queue>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;

typedef property_map<Graph, edge_weight_t>::type WeightMap;

void do_case(int t) {
    int n, e, p, s, d; // #trees, #edges, #parties (species), source, drain

    scanf("%i %i %i %i %i", &n, &e, &p, &s, &d);

    vector<vector<pair<int, int> > > neighbors(n, vector<pair<int, int> >(0)); // pair is (neighbor-id, edge-id)
    vector<vector<int> > duration(e, vector<int>(p));
    vector<pair<int, int> > edges(e);

    for(int ie = 0; ie < e; ++ie) {
        int b, e; // begin, end
        scanf("%i %i", &b, &e);

        neighbors[b].push_back(make_pair(e, ie));
        neighbors[e].push_back(make_pair(b, ie));
        edges[ie] = make_pair(e, b);

        for(int ip = 0; ip < p; ++ip) {
            scanf("%i", &duration[ie][ip]);
        }
    }

    vector<int> hives(p);

    for(int ip = 0; ip < p; ++ip) {
        scanf("%i", &hives[ip]);
    }

    for(int ip = 0; ip < p; ++ip) {
        priority_queue<pair<int, int> > pq; // pair is (-duration, node-id)

        vector<bool> visited(n, false); // no trees visited

        int c_visited = 1;
        visited[hives[ip]] = true;
        for(pair<int, int> neighbor : neighbors[hives[ip]]) {
            pq.push(make_pair(-duration[neighbor.second][ip], neighbor.first));
        }

        while(c_visited < n) {
            pair<int, int> top = pq.top();
            pq.pop();

            if(!visited[top.second]) {
                visited[top.second] = true;
                c_visited++;

                for(pair<int, int> neighbor : neighbors[top.second]) {
                    if(!visited[neighbor.first]) {
                        pq.push(make_pair(-duration[neighbor.second][ip], neighbor.first));
                    }
                }
            }

        }

        while(pq.size()) { // remaining edges are not in the private network
            for(int ie = 0; ie < e; ++ie) {
                if(duration[ie][ip] == -pq.top().first) {
                    duration[ie][ip] = 999999;
                    break;
                }
            }
            pq.pop();
        }
    }

    Graph g(n);
    WeightMap map_weight = get(edge_weight, g);

    for(int ie = 0; ie < e; ++ie) {
        for(int ip = 0; ip < p; ++ip) {
            // printf("ie: %i, ip: %i, duration: %i\n", ie, ip, duration[ie][ip]);
            duration[ie][0] = min(duration[ie][0], duration[ie][ip]);
        }

        if(duration[ie][0] < 999999) {
            // printf("dropping\n");
            Edge e;
            bool success;
            tie(e, success) = add_edge(edges[ie].first, edges[ie].second, g);
            map_weight[e] = duration[ie][0];
        }
    }

    vector<int> map_distance(n);

    dijkstra_shortest_paths(g, s, distance_map(&map_distance[0]));

    printf("%i\n", map_distance[d]);
}

int main() {

    int t;
    scanf("%i", &t);

    while(t--) {
        do_case(t);
    }

    return 0;
}
