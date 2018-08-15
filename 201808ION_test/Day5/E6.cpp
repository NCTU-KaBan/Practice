#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e3 + 5;
struct Graph { 
    struct Edge; int n;
    struct Node : vector<Edge*> {
        LL d;
        Node () { d = INF; }
    }_memN[MAXN], *node[MAXN];
    struct Edge {
        Node *u, *v;
        LL w;
        Edge() {}
        Edge(Node *_u, Node *_v, LL _w) {
            u = _u, v = _v, w = _w;
        }
    }_memE[MAXN * MAXN], *ptr;
    Graph(int _n) : n(_n) {
        for (int i = 0 ; i < n ; i++)
            node[i] = _memN + i;
        ptr = _memE;
    }
    void addEdge(int u, int v, LL w) {
        node[u]->push_back(new (ptr++) Edge(node[u], node[v], w));
        node[v]->push_back(new (ptr++) Edge(node[v], node[u], w));
    }
    LL min_dist(int s, int t) {
        queue<Node*> q; q.push(node[s]); node[s]->d = 0;
        while (q.size()) {
            Node *u = q.front(); q.pop();
            for (auto e : *u) {
                Node *v = e->v;
                if (u->d + e->w < v->d) {
                    v->d = u->d + e->w;
                    q.push(v);
                }
            }
        }
        return node[t]->d;
    }
};
int main() {
    int t; cin >> t; while (t--) {
        int n, m, s, t; cin >> n >> m >> s >> t;
        s--, t--;
        Graph *sol = new Graph(n);
        for (int i = 0 ; i < m ; i++) {
            int u, v; LL w;
            cin >> u >> v >> w;
            u--, v--;
            sol->addEdge(u, v, w);
        }
        cout << sol->min_dist(s, t) << '\n';
        delete sol;
    }
}
