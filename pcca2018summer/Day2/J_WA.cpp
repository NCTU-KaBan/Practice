#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > G;
vector<int> res;
bool check(int u) {
    if (G[u].size() % 2) return false;
    res.push_back(u);
    for (auto v : G[u]) {
        if (!check(v)) return false;
    }
    return true;
}
int main() {
    int n; cin >> n;
    G.resize(n);
    for (int i = 0 ; i < n ; i++) {
        int v; cin >> v; if (v == 0) continue;
        G[v - 1].push_back(i);
    }
    if (check(0)) {
        cout << "YES\n";
        for (int i = 0 ; i < res.size() ; i++)
            cout << res[i] + 1 << '\n';
    } else cout << "NO\n";
}
