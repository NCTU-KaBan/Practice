#include <bits/stdc++.h>
using namespace std;
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e3 + 5;
int x, n, m, T;
long long dp[MAXN][MAXN], sp[MAXN], co[MAXN];
vector<vector<int> > G;
long long solve(int u, int t) {
    if (t < 0) return INF;
    if (~dp[u][t]) return dp[u][t];
    dp[u][t] = INF;
    dp[u][t] = min(dp[u][t], solve(u, t - sp[u]) + co[u]);
    for (auto v : G[u]) {
        dp[u][t] = min(dp[u][t], solve(v, t - sp[u] - T) + co[u]);
    }
    return dp[u][t];
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> x >> n >> m >> T;
    G.clear(); G.resize(n + 5);
    for (int i = 0 ; i < m ; i++) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1 ; i <= n ; i++)
        cin >> sp[i] >> co[i];
    memset(dp, -1, sizeof(dp));
    dp[1][sp[1]] = co[1];
    if (sp[1] * 2 > x) {
        cout << "It is a trap.\n";
        return 0;
    }
    long long ans = solve(1, x);
    if (ans == INF) cout << "It is a trap.\n";
    else cout << ans << '\n';
}
