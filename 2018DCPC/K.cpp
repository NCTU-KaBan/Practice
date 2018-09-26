#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int lgN  = __lg(MAXN);
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
struct Edge {
    int u, v; LL w;
};
int pa[MAXN];
int _find(int x) { return pa[x] == x ? x : pa[x] = _find(pa[x]); }
struct Tree {
    struct Node : vector<Node*> {
        int dep, v;
        Node* pa[lgN];
        int sum[lgN];
        Node() {
            clear(), dep = -1;
            for (int i = 0 ; i < lgN ; i++)
                sum[i] = 0;
        }
    }_memN[MAXN], *node[MAXN];
    int V;
    Tree(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
    }
    inline void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
    }
    void solve() {
        dfs(node[0], node[0], 0);
    }
    void dfs(Node *u, Node *p, int dep) {
        u->pa[0] = p; u->dep = dep;
        u->sum[0] = u->v;
        for (int i = 1 ; i < lgN ; i++) {
            u->pa[i] = u->pa[i - 1]->pa[i - 1];
            u->sum[i] = u->sum[i - 1] + u->pa[i - 1]->sum[i - 1];
        }
        for (auto v : *u)
            if (!~v->dep)
                dfs(v, u, dep + 1);
    }
    LL query(int _u, int _v) {
        Node *u = node[_u], *v = node[_v];
        LL ans = 0;
        if (u->dep < v->dep) swap(u, v);
        for (int i = lgN - 1 ; ~i ; i--)
            if (u->pa[i]->dep >= v->dep)
                ans += u->sum[i], u = u->pa[i];
        if (u == v) return ans;
        for (int i = lgN - 1 ; ~i ; i--) 
            if (u->pa[i] != v->pa[i])
                ans += u->sum[i] + v->sum[i],
                u = u->pa[i], v = v->pa[i];
        return ans + u->sum[0] + v->sum[0];
    }
    void Print() {
        Print(node[0]);
        for (int i = 0 ; i < V ; i++) {
            cout << i << " : ";
            for (int j = 0 ; j < lgN ; j++)
                cout << node[i]->sum[j] << ' ';
            cout << '\n';
        }
    }
    void Print(Node *u) {
        if (!u) return ;
        cout << u - _memN << ' ' << u->dep << ' ' << u->v << '\n';
        for (auto v : *u)
            Print(v);
    }
};
void dfs(int u, int p, int d, vector<vector<int> > &G, vector<int> &dep) {
    dep[u] = d;
    for (auto v : G[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1, G, dep);
    }
}
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, q; cin >> n >> q;
        vector<Edge> edges;
        for (int i = 0 ; i < n ; i++) {
            int u, v, w; cin >> u >> v >> w; u--, v--;
            edges.push_back({u, v, w});
        }
        for (int i = 0 ; i < n ; i++) pa[i] = i;
        int extra = -1;
        for (int i = 0 ; i < n ; i++) {
            Edge e = edges[i];
            int x = _find(e.u), y = _find(e.v);
            if (x != y) {
                pa[x] = y;
                continue;
            }
            extra = i;
        }
        vector<vector<int> > G(n);
        for (int i = 0 ; i < n ; i++) {
            if (i == extra) continue;
            Edge e = edges[i];
            G[e.u].push_back(e.v);
            G[e.v].push_back(e.u);
        }
        vector<int> dep(n, -1);
        dfs(0, -1, 0, G, dep);
        for (int i = 0 ; i < n ; i++) {
            if (extra == i) continue;
            Edge &e = edges[i];
            if (dep[e.u] < dep[e.v]) continue;
            swap(e.u, e.v);
        }
        Tree *sol = new Tree(n);
        for (int i = 0 ; i < n ; i++) {
            if (i == extra) continue;
            Edge e = edges[i];
            sol->addEdge(e.u, e.v);
            sol->node[e.v]->v = e.w;
        }
        sol->solve();
        // sol->Print();
        while (q--) {
            Edge e = edges[extra];
            int u, v; cin >> u >> v;
            u--, v--;
            LL ans = INF;
            ans = min(ans, sol->query(u, v));
            ans = min(ans, sol->query(u, e.u) + sol->query(e.v, v) + e.w);
            ans = min(ans, sol->query(u, e.v) + sol->query(e.u, v) + e.w);
            cout << ans << '\n';
        }
        delete sol;

    }
}
