#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL solve(LL n, LL k, LL s) {
    if (s == 0 && k == 0) return 1;
    LL ret = 0;
    for (int i = 1 ; i <= n ; i++) {
        ret += solve(i - 1, k - 1, s - i);
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    LL n, k, s; while (cin >> n >> k >> s) {
        if (n == 0 && k == 0 && s == 0) break;
        cout << solve(n, k, s) << '\n';
    }
    
}
