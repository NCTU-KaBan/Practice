#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int INF = 0x3f3f3f3f;
struct Graph {
    struct Edge; int n;
    struct Node : vector<Edge*>{
        int dp[1<<MAXN];
        int min_dist[MAXN];
        Node() { 
            memset(dp, INF, sizeof(dp)); 
            memset(min_dist, INF, sizeof(min_dist));
        }
    }_memN[MAXN], *node[MAXN];
    struct Edge {
        Node *u, *v;
        int w;
        Edge (Node *_u = NULL, Node *_v = NULL, int _w = 0) {
            u = _u, v = _v;
            w = _w;
        }
    }_memE[MAXN * MAXN], *ptr;
    Graph(int _n) : n(_n) {
        ptr = _memE;
        for (int i = 0 ; i < n ; i++) {
            node[i] = _memN + i;
            node[i]->dp[(1<<i)] = 0;
            node[i]->min_dist[i] = 0;
        }
    }
    void addEdge(int u, int v, int w) {
        node[u]->push_back(new (ptr++) Edge(node[u], node[v], w));
        node[v]->push_back(new (ptr++) Edge(node[v], node[u], w));
        node[u]->min_dist[v] = node[v]->min_dist[u] = w;
    }
    // dp[i][S] 停在i而且經過S的狀態的最少公里數
    void floyd() {
        for (int k = 0 ; k < n ; k++)
            for (int i = 0 ; i < n ; i++)
                for (int j = 0 ; j < n ; j++)
                    node[i]->min_dist[j] = min(node[i]->min_dist[k] + node[k]->min_dist[j], node[i]->min_dist[j]);
    }
    int solve(int u, int S) {
        if (node[u]->dp[S] != INF) return node[u]->dp[S];
        for (int i = 0 ; i < n ; i++) {
            if (S & (1 << i) && i != u) 
                node[u]->dp[S] = min(node[u]->dp[S], solve(i, S ^ (1 << u)) + node[i]->min_dist[u]);
        }
        return node[u]->dp[S];
    }
};
int main() {
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        Graph *sol = new Graph(n);
        for (int i = 0 ; i < m ; i++) {
            int u, v, w; cin >> u >> v >> w;
            u--, v--;
            sol->addEdge(u, v, w);
        }
        sol->floyd();
        int ans = INF;
        for (int i = 0 ; i < n ; i++)
            ans = min(ans, sol->solve(i, (1<<n) - 1));
        cout << ans << '\n';
        delete sol;
    }
}
