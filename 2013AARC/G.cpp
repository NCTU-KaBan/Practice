#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int A, B;
int a, b, C = ~(1<<31), M = (1<<16)-1;
int r() {
	a = 36969 * (a & M) + (a >> 16);
	b = 18000 * (b & M) + (b >> 16);
	return (C & ((a << 16) + b)) % 1000000;
}
struct T {
    int x, y, z;
};
bool lower(T a, T b) {
    return a.x < b.x && a.y < b.y && a.z < b.z;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int m, n; while (cin >> m >> n >> A >> B) {
        if (m == 0 && n == 0 && A == 0 && B == 0) break;
        a = A, b = B;
        vector<T> data(n + m);
        for (int i = 0 ; i < m ; i++)
            cin >> data[i].x >> data[i].y >> data[i].z;
        for (int i = m ; i < n + m ; i++) {
            data[i].x = r();
            data[i].y = r();
            data[i].z = r();
        }
        vector<vector<int> > G(n + m);
        vector<int> deg(n + m, 0);
        for (int i = 0 ; i < n + m ; i++) {
            for (int j = 0 ; j < n + m ; j++) {
                if (lower(data[i], data[j])) {
                    G[j].push_back(i);
                    deg[i]++;
                }
            }
        }
        vector<int> dp(n + m, 0);
        queue<int> q;
        for (int i = 0 ; i < n + m ; i++)
            if (deg[i] == 0) q.push(i), dp[i] = 1;
        while (q.size()) {
            int p = q.front(); q.pop();
            for (auto v : G[p]) {
                if (dp[v] < dp[p] + 1) { 
                    dp[v] = dp[p] + 1;
                }
                deg[v]--;
                if (deg[v] == 0) q.push(v);
            }
        }
        int ans = 0;
        for (int i = 0 ; i < n + m ; i++)
            ans = max(ans, dp[i]);
        cout << ans << '\n';
    }

}
