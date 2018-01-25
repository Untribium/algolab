#include<bits/stdc++.h>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS>            Traits;
typedef adjacency_list<vecS, vecS, directedS,
    no_property,
    property<edge_capacity_t, int,
    property<edge_residual_capacity_t, int,
    property<edge_reverse_t, Traits::edge_descriptor> > > >     Graph;

typedef graph_traits<Graph>::vertex_descriptor                  Vertex;
typedef graph_traits<Graph>::edge_descriptor                    Edge;

void flow_edge(int u, int v, property_map<Graph, edge_capacity_t>::type &cm, property_map<Graph, edge_reverse_t>::type &im, Graph &g) {
    Edge e, r;

    tie(e, ignore) = add_edge(u, v, g);
    tie(r, ignore) = add_edge(v, u, g);

    cm[e] = 1; cm[r] = 0;
    im[e] = r; im[r] = e;
}

int main() {

     ios_base::sync_with_stdio(false);
     cin.tie(0);

     int T;
     cin >> T;

     while(T--) {

         int G, S, L;
         cin >> G >> S >> L;

         Graph g(G+S+2);

         property_map<Graph, edge_capacity_t>::type cm = get(edge_capacity, g);
         property_map<Graph, edge_reverse_t>::type im = get(edge_reverse, g);
         property_map<Graph, edge_residual_capacity_t>::type rm = get(edge_residual_capacity, g);

         for(int il = 0; il < L; ++il) {

             int rg, rs;
             cin >> rg >> rs;

             flow_edge(rg, G+rs, cm, im, g);
         }

         for(int ig = 0; ig < G; ++ig) flow_edge(G+S,  ig,    cm, im, g);
         for(int is = 0; is < S; ++is) flow_edge(G+is, G+S+1, cm, im, g);

         push_relabel_max_flow(g, G+S, G+S+1);

         vector<bool> v(G+S+2, false);
         std::queue<int> q;
         q.push(G+S);

         while(q.size()) {
             int top = q.front();
             q.pop();

             graph_traits<Graph>::out_edge_iterator ie, ie_end;
             for(tie(ie, ie_end) = out_edges(top, g); ie != ie_end; ++ie) {
                 int t = target(*ie, g);

                 if(!v[t] && rm[*ie] > 0) {
                     q.push(t);
                     v[t] = true;
                 }
             }
         }

         cout << count(v.begin(), v.begin()+G, false) << " " << count(v.begin()+G, v.begin()+G+S, true) << endl;

         for(int ig = 0; ig < G; ++ig) {
             if(!v[ig]) cout << ig << " ";
         }

         for(int is = 0; is < S; ++is) {
             if(v[G+is]) cout << is << " ";
         }
         cout << endl;
     }

     return 0;
}
