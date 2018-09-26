#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
LL fpow(LL a, LL n) {
    if (n == 0) return 1;
    LL k = fpow(a, n >> 1);
    if (n & 1) return k * k % MOD * a % MOD;
    else return k * k % MOD;
}
LL extgcd(LL a, LL b, LL &x, LL &y){
    if (!b) return x = 1, y = 0, a;
    LL res = extgcd(b, a%b, y, x);
    return y -= a / b * x, res;
}
LL modInv(LL a, LL m){
    LL x, y, d = extgcd(a, m, x, y);
    return d == 1 ? (x + m) % m : -1;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    LL n, m, c;
    cin >> n >> m >> c;
    LL ans = 0;
    for (LL i = 0 ; i < m ; i++)
    	ans += fpow(c, n * n * __gcd(i, m)),
    	ans %= MOD;
    cout << ans * modInv(m, MOD) % MOD << '\n';
}
