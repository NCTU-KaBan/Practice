#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
vector<vector<int> > G;
int vis[MAXN], stamp = 1;
map<int, int> M;
int sz[MAXN];
int dfs(int u) {
    vis[u] = stamp++;
    M[vis[u]] = u;
    sz[u] = 1;
    for (auto v : G[u]) {
        sz[u] += dfs(v);
    }
    return sz[u];
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    G.resize(n);
    for (int i = 1 ; i < n ; i++) {
        int v; cin >> v; v--;
        G[v].push_back(i);
    }
	memset(sz, 0, sizeof(sz));
    dfs(0);
    while (q--) {
        int u, k; cin >> u >> k; u--;
        if (sz[u] < k) cout << -1 << '\n';
        else {
            k--;
            cout << M[vis[u] + k] + 1 << '\n';
        }
    }
}
