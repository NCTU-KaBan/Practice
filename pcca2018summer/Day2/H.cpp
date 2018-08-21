#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > G;
double dfs(int u, int p) {
    if (G[u].size() == 1 && u != 0) return 0;
    double res = 0;
    for (auto v : G[u]) {
        if (v == p) continue;
        res += dfs(v, u);
    }
    if (u == 0) res = res / (G[u].size()) + 1;
    else res = res / (G[u].size() - 1) + 1;
    return res;
}
int main() {
    int n; cin >> n;
    G.resize(n);
    for (int i = 0 ; i < n - 1;  i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    if (n == 1) cout << 0 << '\n';
    else cout << fixed << setprecision(15) << dfs(0, 0) << '\n';
}
