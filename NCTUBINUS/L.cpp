#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
const int MAXN = 55;
typedef pair<int, int> pii;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        set<int> app;
        int B[MAXN][MAXN]; memset(B, -1, sizeof(B));
        for (int i = 1 ; i <= n ; i++) {
            for (int j = 1 ; j <= m ; j++) {
                cin >> B[i][j];
                if (B[i][j]) app.insert(B[i][j]);
            }
        }
        vector<int> data; data.push_back(0);
        for (auto num : app) data.push_back(num);
        long long ans = 0;
        for (int k = 1 ; k < data.size() ; k++) {
            int num = data[k];
            if (num == 0) continue;
            bool vis[MAXN][MAXN]; memset(vis, false, sizeof(vis));
            for (int i = 1 ; i <= n ; i++) {
                for (int j = 1 ; j <= m ; j++) {
                    if (vis[i][j]) continue;
                    if (B[i][j] < num) continue;
                    queue<pii> q; q.push({i, j});
                    vis[i][j] = true;
                    while (q.size()) {
                        pii p = q.front(); q.pop();
                        if (B[p.F][p.S] == num) { 
                            ans++;
                        }
                        for (int d = 0 ; d < 4 ; d++) {
                            pii next = {p.F + dx[d], p.S + dy[d]};
                            if (B[next.F][next.S] < num) { 
                                ans += num - data[k - 1];
                            }
                            if (B[next.F][next.S] < num) continue;
                            if (vis[next.F][next.S]) continue;
                            q.push(next);
                            vis[next.F][next.S] = true;
                        }
                    }
                }
            }
        }
        cout << ans << '\n';
    }
}
