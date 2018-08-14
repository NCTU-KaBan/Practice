#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXM = 2e6 + 5;
const int INF  = 0x3f3f3f3f;
struct Graph {
    struct Edge; int n;
    struct Node : vector<Edge*> {
        int d;
        Node() { d = INF; }
    }_memN[MAXN], *node[MAXN];
    struct Edge {
        Node *u, *v;
        int w;
        Edge() {}
        Edge(Node *_u, Node *_v, int _w) {
            u = _u, v = _v, w = _w;
        }
    }_memE[MAXM], *ptr;
    Graph(int _n) : n(_n) {
        for (int i = 0 ; i < n ; i++)
            node[i] = _memN + i;
        ptr = _memE;
    }
    void addEdge(int u, int v, int w) {
        node[u]->push_back(new (ptr++) Edge(node[u], node[v], w));
    }
    void solve() {
        node[0]->d = 0;
        queue<Node*> q; q.push(node[0]);
        while (q.size()) {
            Node *p = q.front(); q.pop();
            for (auto e : *p) {
                Node *v = e->v;
                if (v->d > p->d + e->w) {
                    q.push(v);
                    v->d = p->d + e->w;
                }
            }
        }
        for (int i = 0 ; i < n ; i++) {
            if (node[i]->d == INF) cout << -1;
            else cout << node[i]->d;
            cout << ' ';
        }
        cout << '\n';
    }
};
int main() {
    int t; cin >> t; while (t--) {
        int n, m, k; cin >> n >> m >> k;
        Graph *sol = new Graph(n);
        for (int i = 0 ; i < m ; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            sol->addEdge(u, v, 1);
        }
        for (int i = 0 ; i < k ; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            sol->addEdge(u, v, 0);
        }
        sol->solve();
        delete sol;
    }
}
