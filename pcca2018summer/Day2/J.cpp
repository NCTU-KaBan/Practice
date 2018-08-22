#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > G;
vector<int> ans;
int rt;
const int MAXN = 2e5 + 5;
bool dfs(int u) {
    int cnt = G[u].size();
    if (u != rt) cnt++;
    for (auto v : G[u])
        cnt -= dfs(v);
    if (cnt % 2 == 0) {
        ans.push_back(u);
        return true;
    } else return false;
}
int vis[MAXN];
void Print(int u) {
    if (vis[u]) return ;
    vis[u] = true;
    cout << u + 1 << '\n';
    for (auto v : G[u]) {
        if (vis[v]) continue;
        Print(v);
    }
}
int main() {
    int n; cin >> n; G.resize(n);
    for (int i = 0 ; i < n ; i++) {
        int p; cin >> p;
        if (p == 0) {
            rt = i;
            continue;
        }
        G[p - 1].push_back(i);
    }
    if (dfs(rt)) {
        cout << "YES\n";
        memset(vis, false, sizeof(vis));
        for (auto u : ans) {
            Print(u);
        }
    } else cout << "NO\n";
}
