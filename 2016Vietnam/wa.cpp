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
        bool legal = false;
        while (x && !legal) {
            if (x % 10 == 8 || x % 10 == 6) legal = true;
            x /= 10;
        }
        if (legal && i % 8 == 0) dp[i] = dp[i - 1] + 1;
        else dp[i] = dp[i - 1];
    }
    
    LL dpzero[30]; memset(dpzero, 0, sizeof(dpzero));
    dpzero[3] = dp[1000];
    LL BASE = 1000;
    for (int i = 4 ; i <= 18 ; i++) {
        dpzero[i] = dpzero[i - 1] * 8 + 2 * BASE / 8;
        BASE *= 10;
    }

    int q; cin >> q; while (q--) {
        LL n; cin >> n;
        stack<int> stk;
        LL sum = 0;
        bool legal = false;
        LL target = n;
        while (n) {
            if (n % 10 == 8 || n % 10 == 6) legal = true;
            stk.push(n % 10);
            n /= 10;
        }
        if (target % 8 && legal) sum = 1;

        bool ok = false;
        while (stk.size() > 3) {
            int p = stk.top(); stk.pop();
            if (p == 8) {
                sum += 7 * dpzero[stk.size()] + 1 * pow10123[stk.size()] / 8 + 1;
                ok = true;
                break;
            }
            if (p == 6) {
                sum += 6 * dpzero[stk.size()] + 1;
                ok = true;
                break;
            }
            if (p <= 5) {
                sum += p * dpzero[stk.size()];
            } else if (p <= 7) { // 7
                sum += 6 * dpzero[stk.size()] + pow10123[stk.size()] / 8;
            } else { // 9
                sum += 7 * dpzero[stk.size()] + 2 * pow10123[stk.size()] / 8;
            }
        }
        LL total = 0;
        while (stk.size()) {
            int p = stk.top(); stk.pop();
            total *= 10;
            total += p;
        }
        if (!ok) {
            sum += dp[total];
        } else {
            sum += total / 8;
        }
        cout << sum << '\n';

    }
}
