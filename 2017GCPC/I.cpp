#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> data;
    for (int i = 0 ; i < n ; i++) {
        int input; cin >> input;
        data.push_back(input);
    }
    if (m >= n) {
        cout << 0 << '\n';
        return 0;
    }
    vector<int> dp(n + m + 1, 0); dp[m] = 0;
    for (int i = m ; i < n + m ; i++) {
        dp[i + 1] = max(dp[i], dp[i + 1]);
        dp[i + m] = max(dp[i] + data[i], dp[i + m]);
    }
    int ans = 0;
    for (int i = m ; i < n + m ; i++)
        ans = max(ans, dp[i]);
    cout << ans << '\n';
}
