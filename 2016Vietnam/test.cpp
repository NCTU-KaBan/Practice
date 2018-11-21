#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pow10123[20];
LL dp[10000001]; 
int main() {
    pow10123[0] = 1;
    for (int i = 1 ; i < 20 ; i++)
        pow10123[i] = pow10123[i - 1] * 10;

    LL cnt = 0;
    memset(dp, 0, sizeof(dp));
    int j = 3;
    for (LL i = 1 ; i <= 10000000 ; i++) {
        LL x = i;
        int legal = 0;
        while (x && !legal) {
            if (x % 10 == 8 || x % 10 == 6) legal++;
            x /= 10;
        }
        if (legal && i % 8 == 0) dp[i] = dp[i - 1] + legal;
        else dp[i] = dp[i - 1];
    }

    int q; cin >> q; while (q--) {
        int n; cin >> n;
        int target = n;

        int legal = 0;
		while (n) {
            if (n % 10 == 8 || n % 10 == 6) legal++;
            n /= 10;
        }
        LL sum = 0;
        if (target % 8 && legal) sum = legal;

        cout << dp[target] + sum  << '\n';
    }
}
