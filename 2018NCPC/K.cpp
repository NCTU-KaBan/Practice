#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
LL extgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) return x = 1, y = 0, a;
    LL res = extgcd(b, a % b, y, x);
    return y -= a / b * x, res;
}
LL modInv(LL a, LL m) {
    LL x, y, d = extgcd(a, m, x, y);
    return d == 1 ? (x + m) % m : -1;
}
LL trans(LL x) {
    while (x < 0) x += MOD;
    return x % MOD;
}
const int MAXN = 2505;
LL fact[MAXN], inv[MAXN];
LL C(int n, int m) {
    return fact[n] * inv[n - m] % MOD * inv[m] % MOD;
}
LL fpow(int a, int m) {
    if (m == 0) return 1;
    LL k = fpow(a, m / 2);
    if (m % 2) return k * k % MOD * a % MOD;
    else return k * k % MOD;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    fact[0] = 1; inv[0] = 1;
    for (int i = 1 ; i < MAXN ; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = modInv(fact[i], MOD);
    }
    LL n, k; cin >> n >> k;
    for (int i = 0 ; i < n - 1 ; i++) {
        int tmp; cin >> tmp;
    }
    LL ans = 0; bool flag = 1;
    for (int i = k ; i >= 1 ; i--) {
        LL sum = C(k, i) * i % MOD * fpow(i - 1, n - 1) % MOD;
        if (flag) ans += sum;
        else ans -= sum;
        flag ^= 1;
        ans = trans(ans);
    }
    cout << ans << '\n';

}
