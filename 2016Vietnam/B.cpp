#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
struct B {
    LL pos, hei, idx;
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<B> data(n + 1);
        for (int i = 1 ; i <= n ; i++) cin >> data[i].pos;
        for (int i = 1 ; i <= n ; i++) cin >> data[i].hei;
        for (int i = 1 ; i <= n ; i++) data[i].idx = i;

        vector<LL> pre; pre.push_back(0);
        for (int i = 1 ; i <= n ; i++) {
            pre.push_back(pre.back() + data[i].hei);
        }

        vector<LL> ans; ans.push_back(0);
        vector<B> dq; dq.push_back({-1, INF, 0});
        for (int i = 1 ; i <= n ; i++) {
            B b = data[i];
            while (dq.size() != 1 && dq.back().hei < b.hei) dq.pop_back();
            LL sum = b.hei * (b.pos - dq.back().pos - 1) - (pre[b.idx - 1] - pre[dq.back().idx]);
            ans.push_back(ans[dq.back().idx] + sum);
            dq.push_back(b);
        }
/*
        for (auto x : ans) cout << x << ' ';
        cout << '\n';
*/
        int q; cin >> q; while (q--) {
            LL m; cin >> m;
            cout << lower_bound(ans.begin(), ans.end(), m) - ans.begin() - 1 << '\n';
        }
    }
}
