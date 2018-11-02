#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<int> F(n);
        for (int i = 1 ; i < n ; i++)
            cin >> F[i];
        vector<int> dp(n, 0);
        dp[0] = F[1] * n;

        for (int i = 0 ; i < n - 1 ; i++)
            for (int j = i ; j < n - 1 ; j++) 
                dp[j] = max(dp[j], dp[j - i] + F[i + 1] - F[1]);
        cout << dp[n - 2] << '\n';
    }
}

