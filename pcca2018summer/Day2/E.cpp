#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 5;
vector<vector<int> > G;
int tem[MAXN], rt, sum;
vector<int> ans;
int dfs(int u) {
    for (auto v : G[u]) {
        tem[u] += dfs(v);
    }
    if (tem[u] == (sum / 3)) {
        if (u != rt) ans.push_back(u);
        return 0;
    } 
    return tem[u];
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n; G.resize(n);
    sum = 0;
    for (int i = 0 ; i < n ; i++) {
        int p; cin >> p >> tem[i];
        sum += tem[i];
        if (p == 0) rt = i;
        else {
            G[p - 1].push_back(i);
        }
    }
    if (abs(sum) % 3) cout << -1 << '\n';
    else {
        dfs(rt);
        if (ans.size() >= 2) {
            cout << ans[0] + 1 << ' ' << ans[1] + 1 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}
