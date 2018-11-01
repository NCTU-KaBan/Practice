#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        int B[MAXN][MAXN];
        long long ans = 0;
        memset(B, 0, sizeof(B));
        for (int i = 1 ; i <= n ; i++) {
            for (int j = 1 ; j <= m ; j++) {
                cin >> B[i][j];
                if (B[i][j]) ans++;
            }
        }
        for (int i = 0 ; i <= n ; i++) {
            for (int j = 0 ; j <= m ; j++) {
                ans += abs(B[i][j] - B[i][j + 1]);
                ans += abs(B[i][j] - B[i + 1][j]);
            }
        }
        cout << ans << '\n';
    }
}
