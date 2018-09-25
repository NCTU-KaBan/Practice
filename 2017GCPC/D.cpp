#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > G;
vector<bool> vis;
map<string, int> id;
int ID(string s) {
    int num = id.size();
    if (id.find(s) == id.end()) id[s] = num;
    return id[s];
}
void bfs(int s) {
    fill(vis.begin(), vis.end(), false);
    queue<int> q; q.push(s);
    while (q.size()) {
        int p = q.front(); q.pop();
        vis[p] = true;
        for (auto v : G[p]) {
            if (vis[v]) continue;
            vis[v] = true;
            q.push(v);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    G.clear(); G.resize(2 * n);
    vis.clear(); vis.resize(2 * n);
    for (int i = 0 ; i < n ; i++) {
        string u, a, b, c, v;
        cin >> u >> a >> b >> c >> v;
        G[ID(v)].push_back(ID(u));
    }
    for (int i = 0 ; i < m ; i++) {
        string u, tmp, v;
        cin >> u >> tmp >> tmp >> tmp >> v;
        if (!id.count(u) || !id.count(v)) {
            cout << "Pants on Fire\n";
            continue;
        }
        bfs(ID(u));
        bool isV = vis[ID(v)];
        bfs(ID(v));
        bool isU = vis[ID(u)];
        if (!isV && isU) {
            cout << "Fact\n";
        } else if (isV && !isU) {
            cout << "Alternative Fact\n";
        } else {
            cout << "Pants on Fire\n";
        }
    }
}
