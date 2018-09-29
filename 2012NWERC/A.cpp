#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define F first
#define S second
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 4005;
const int MAXM = 400005;
typedef pair<LL, LL> pLL;
struct Graph { int V;
    struct Node; struct Edge;
    struct Node : vector<Edge*> {
        bool inq; Edge *pa; LL a, d;
        Node() { clear(); }
    }_memN[MAXN], *node[MAXN];
    struct Edge {
        Node *u, *v; Edge *rev;
        LL c, f, _c; Edge() {}
        Edge(Node *u, Node *v, LL c, LL _c, Edge *rev) : u(u), v(v), c(c), f(0), _c(_c), rev(rev) {}
    }_memE[MAXM], *ptrE;
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
        ptrE = _memE;
    }
    void addEdge(int u, int v, LL c, LL _c) {
        *ptrE = Edge(node[u], node[v], c, _c, ptrE + 1);
        node[u]->push_back(ptrE++);
        *ptrE = Edge(node[v], node[u], 0, -_c, ptrE - 1);
        node[v]->push_back(ptrE++);
    }
    Node *s, *t;
    bool SPFA() {
        for (int i = 0 ; i < V ; i++) node[i]->d = INF, node[i]->inq = false;
        queue<Node*> q; q.push(s); s->inq = true;
        s->d = 0, s->pa = NULL, s->a = INF;
        while (q.size()) {
            Node *u = q.front(); q.pop(); u->inq = false;
            for (auto &e : *u) {
                Node *v = e->v;
                if (e->c > e->f && v->d > u->d + e->_c) {
                    v->d = u->d + e->_c;
                    v->pa = e; v->a = min(u->a, e->c - e->f);
                    if (!v->inq) q.push(v), v->inq = true;
                }
            }
        }
        return t->d != INF;
    }
    pLL maxFlowMinCost(int _s, int _t) {
        s = node[_s], t = node[_t];
        pLL res = make_pair(0, 0);
        while (SPFA()) {
            res.F += t->a;
            res.S += t->d * t->a;
            for (Node *u = t ; u != s ; u = u->pa->u) {
                u->pa->f += t->a;
                u->pa->rev->f -= t->a;
            }
        }
        return res;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        Graph *sol = new Graph(2 * n + 5);
        for (int i = 0 ; i < m ; i++) {
            int u, v; LL c;
            cin >> u >> v >> c;
            sol->addEdge(u + n, v, 1, c);
        }
        sol->addEdge(0, 1, 2, 0);
        for (int i = 2 ; i <= n ; i++) {
            sol->addEdge(i, i + n, 1, 0);
        }
        sol->addEdge(1, 1 + n, 2, 0);
        pLL ans = sol->maxFlowMinCost(0, n);
        cout << ans.S << '\n';
        delete sol;
    }
}
