#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Edge {
    int u, v;
    LL w;
    bool operator < (const Edge &rhs) const {
        return w < rhs.w;
    }
};
vector<int> pa;
int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        LL n, m, l, sn;
        cin >> n >> m >> l >> sn;
        vector<int> s; 
        for (int i = 0 ; i < sn ; i++) {
            int num; cin >> num; s.push_back(num);
        }
        
        vector<Edge> data;
        for (int i = 0 ; i < m ; i++) {
            int u, v, w; cin >> u >> v >> w;
            data.push_back({u, v, w});
        }
        sort(data.begin(), data.end());
        
        pa.clear(); pa.resize(n + 5);
        for (int i = 1 ; i <= n ; i++)
            pa[i] = i;
        for (int i = 0 ; i < sn ; i++) {
            pa[s[i]] = s[0];
        }

        int cnt = 0;
        LL ans = 0;
        for (int i = 0 ; i < m ; i++) {
            Edge e = data[i];
            int x = find(e.u);
            int y = find(e.v);
            if (x != y) {
                pa[x] = y;
                cnt++;
                ans += e.w;
            }
            if (cnt == n - sn) break;
        }
        cout << ans + l * cnt << '\n';
    }
}
