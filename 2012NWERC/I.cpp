#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2000 + 5;
struct Graph {
    struct Node : vector<Node*> {
        int dfn, low, scc;
        bool in_stk;
        Node() {
            clear();
            dfn = low = scc = -1;
            in_stk = false;
        }
    }_memN[MAXN], *node[MAXN];
    int V;
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++) 
            node[i] = _memN + i;
    }
    void addEdge(int u, int v) {
        node[u]->push_back(node[v]);
    }

    int stamp, scc_num; stack<Node*> stk;
    int findSCC() {
        stamp = scc_num = 0;
        for (int i = 0 ; i < V ; i++) {
            Node *u = node[i];
            if (!~u->dfn)
                Tarjan(u);
        }
        return scc_num;
    }
    void Tarjan(Node *u) {
        u->dfn = u->low = stamp++;
        stk.push(u); u->in_stk = true;
        for (auto to : *u) {
            if (!~to->dfn) {
                Tarjan(to);
                u->low = min(u->low, to->low);
            } else if (to->in_stk)
                u->low = min(u->low, to->dfn);
        }
        if (u->dfn == u->low) {
            Node *v;
            do {
                v = stk.top(); stk.pop();
                v->scc = scc_num;
                v->in_stk = false;
            } while (v != u);
            scc_num++;
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        Graph *sol = new Graph(n * 2);
        for (int i = 0 ; i < m ; i++) {
            int u, v; cin >> u >> v;
            if (u < 0) u = -u, u += n;
            if (v < 0) v = -v, v += n;
            u--, v--;
            sol->addEdge((u + n) % (2 * n), v);
            sol->addEdge((v + n) % (2 * n), u);
        }
        sol->findSCC();
        bool legal = true;
        for (int i = 0 ; i < n && legal; i++)
            if (sol->node[i]->scc == sol->node[i + n]->scc)
                legal = false;
        if (legal && sol->node[0]->scc < sol->node[n]->scc) cout << "yes\n";
        else cout << "no\n";
        delete sol;
    }
}
