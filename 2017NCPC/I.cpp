#include <bits/stdc++.h>
using namespace std;
map<string, int> id;
int ID(string s) {
    if (id.count(s)) return id[s];
    int sz = id.size();
    id[s] = sz;
    return id[s];
}
const int INF = 0x3f3f3f3f;
const int MAXN = 505;
bool vis[MAXN];
int d[MAXN][MAXN], start;
string _name[MAXN];
vector<string> ans;
vector<vector<int> > G;
bool dfs(int i) {
    for (auto v : G[i]) {
        if (d[v][v] != d[start][start]) continue;
        if (vis[v]) { 
            if (v == start && ans.size() == d[start][start]) return true;
            continue;
        }
        if (ans.size() >= d[start][start]) return false;
        ans.push_back(_name[v]);
        vis[v] = true;
        if (dfs(v)) return true;
        ans.pop_back();
        vis[v] = false;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for (int i = 0 ; i < n ; i++) {
        cin >> _name[i];
        ID(_name[i]);
    }
    G.clear(); G.resize(n);
    memset(d, INF, sizeof(d));
    for (int i = 0 ; i < n ; i++) {
        string name; cin >> name; 
        int m; cin >> m;
        string input; getline(cin, input);
        while (m--) {
            getline(cin, input);
            for (auto &c : input)
                if (!isalpha(c))
                    c = ' ';
            stringstream ss; ss << input;
            string output; bool first = true;
            while (ss >> output) {
                if (first) first = false;
                else {
                    if (d[ID(name)][ID(output)] == INF) {
                        G[ID(name)].push_back(ID(output));
                    }
                    d[ID(name)][ID(output)] = 1;
                }
            }
        }
    }


    for (int k = 0 ; k < n ; k++)
        for (int i = 0 ; i < n ; i++)
            for (int j = 0 ; j < n ; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    bool legal = false;
    for (int i = 0 ; i < n && !legal ; i++)
        if (d[i][i] != INF) 
            legal = true;
    if (!legal) {
        cout << "SHIP IT\n";
        return 0;
    }
    start = -1; int minV = 1000;
    for (int i = 0 ; i < n ; i++) {
        if (minV > d[i][i]) {
            minV = d[i][i];
            start = i;
        }
    }
    memset(vis, false, sizeof(vis));
    vis[start] = true;
    ans.push_back(_name[start]);
    dfs(start);
    for (int i = 0 ; i < ans.size() ; i++)
        cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
}
