#include <bits/stdc++.h>
using namespace std;
const int MAXN = 505;
const int MAXM = 505;
typedef pair<int, int> pii;
int trans(int d) { return 7 - d; }
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    int data[MAXN][MAXM];
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            cin >> data[i][j];
            data[i][j] *= -1;
        }
    }
    pair<int, int> s; cin >> s.first >> s.second;
    s.first--, s.second--;
    queue<pair<pair<int, int>, pair<int, int> > > q;
    int d[MAXN][MAXN]; memset(d, 0, sizeof(d));
    d[s.first][s.second] = data[s.first][s.second];
    q.push({s, {d[s.first][s.second], -1}});
    while (q.size()) {
        pair<pair<int, int>, pair<int, int> > pp = q.front(); q.pop();
        pair<int, int> p = pp.first;
        if (data[p.first][p.second] <= 0) continue;
        int update = min(pp.second.first, d[p.first][p.second]);
        int dir = pp.second.second;
        int dir_cnt = -1;
        for (int dx = -1 ; dx <= 1 ; dx++) {
            for (int dy = -1 ; dy <= 1 ; dy++) {
                if (dx == 0 && dy == 0) continue;
                dir_cnt++;
                if (dir_cnt == trans(dir)) continue;
                pair<int, int> next = make_pair(p.first + dx, p.second + dy);
                if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= m) continue;
                if (d[next.first][next.second] < min(data[next.first][next.second], update)) {
                    d[next.first][next.second] = min(update, data[next.first][next.second]);
                    q.push({next, {update, dir_cnt}});
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++)
            ans += d[i][j];
    cout << ans << '\n';

}
