#include <bits/stdc++.h>
using namespace std;
struct obj {
    int idx, times;
};
queue<obj> q[189000];
int main() {
    int n, t; cin >> n >> t;
    vector<int> data(n);
    for (auto &num : data)
        cin >> num;
    for (int i = 0 ; i < n ; i++)
        q[0].push({i, data[i]});
    for (int T = 0 ; T < t ; T++) {
        for (int i = 0 ; i < 10000 ; i++) {
            if (q[i].empty()) continue;
            q[i].front().times--;
        }
        for (int i = 0 ; i < 10000 ; i++) {
            if (q[i].empty()) continue;
            if (q[i].front().times == 0) {
                obj p = q[i].front(); q[i].pop();
                q[i + 1].push({p.idx, data[p.idx]});
            }
        }
    }
    vector<int> ans(n);
    for (int i = 0 ; i < 10000 ; i++) {
        while (q[i].size()) {
            ans[q[i].front().idx] = i + 1;
            q[i].pop();
        }
    }
    for (int i = 0 ; i < n ; i++)
        cout << ans[i] << '\n';
}
