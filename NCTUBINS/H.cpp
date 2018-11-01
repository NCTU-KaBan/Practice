#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<LL> cnt;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<LL> F(n);
        cnt.resize(n);
        for (int i = 1 ; i <= n ; i++) cin >> F[i];
        cnt[1] = n - 1;
        cnt[n - 1] = 1;
        LL max_total = -1, total = 0;
        do {
            for (int i = 0 ; i < n ; i++)
                total += F[ans[i]];
            max_total = max(max_total, total);
        } while (next());
        cout << max_total << '\n';
    }
}
