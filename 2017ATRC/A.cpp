#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
int k; LL dp[105][2];
LL solve(int l, bool isB) {
    if (l < 0) return 0;
    if (~dp[l][isB]) return dp[l][isB];
    if (isB && l == 0) return dp[l][isB] = 0;
    if (!isB && l == 0) return dp[l][isB] = 1;
    if (isB) {
        return dp[l][isB] = solve(l - k, !isB) + solve(l - 1, !isB);
    } else {
        return dp[l][isB] = solve(l - 1, !isB);
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int l; cin >> l >> k;
    memset(dp, -1, sizeof(dp));
    LL ans = 0;
    for (int i = 1 ; i <= l ; i++) {
        ans += solve(i, true);
    }
    cout << ans << '\n';

}
