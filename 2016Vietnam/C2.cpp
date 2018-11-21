#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pow10123[20];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    pow10123[0] = 1;
    for (int i = 1 ; i < 20 ; i++)
        pow10123[i] = pow10123[i - 1] * 10;

    LL dp[1005]; memset(dp, 0, sizeof(dp));
    for (int i = 1 ; i <= 1000 ; i++) {
        int x = i;
        int legal = 0;
        while (x && !legal) {
            if (x % 10 == 8 || x % 10 == 6) legal++;
            x /= 10;
        }
        if (legal && i % 8 == 0) dp[i] = dp[i - 1] + legal;
        else dp[i] = dp[i - 1];
    }
    int q; cin >> q; while (q--) {
        LL n; cin >> n;
        LL sum = 0, target = n, x = 1;
        while (n) {
            sum += dp[n % 1000] * x;
            x *= 10;
            n /= 1000;
        }
        if (target % 8) {
            while (target) {
                if (target % 10 == 8 || target % 10 == 6) sum++;
                target /= 10;
            }
        }
        cout << sum << '\n';
    }
    
}
