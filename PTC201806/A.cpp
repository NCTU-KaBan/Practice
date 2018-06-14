#include <bits/stdc++.h>
using namespace std;
const int MAXN = 35;
int deg[MAXN], n;
vector<int> G[MAXN];
bool vis[MAXN];
int solve() {
    int target_point = -1;
    for (int i = 0 ; i < n && !~target_point ; i++)
        if (!vis[i])
            target_point = i;
    if (!~target_point) return 0;
    vis[target_point] = true;
    if (deg[target_point] == 0) return 1 + solve();
    if (deg[target_point] == 1) {
        vis[G[target_point][0]] = true;
        for (auto v : G[G[target_point][0]])
            deg[v]--;
        return 1 + solve();
    }
    int res = -1;
    for (auto v : G[target_point]) deg[v]--;
    res = max(res, solve());
    for (auto v : G[target_point]) vis[v] = true;
    res = max(res, solve() + 1);
    return res;
}
int main() {
    int m; cin >> n >> m;
    bool adj[MAXN][MAXN]; memset(adj, true, sizeof(adj));
    for (int i = 0 ; i < n ; i++) adj[i][i] = false;
    while (m--) {
        int u, v; cin >> u >> v;
        adj[u][v] = adj[v][u] = false;
    }
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < n ; j++)
            if (adj[i][j])
                G[i].push_back(j);
    memset(deg, 0, sizeof(deg));
    for (int i = 0 ; i < n ; i++)
        deg[i] = G[i].size();
    memset(vis, false, sizeof(vis));
    cout << solve() << '\n';
}
