#pragma GCC optimize ("O3")
#include <iostream>
#include <cmath>
#include <map>
using namespace std;
typedef long long LL;
LL extgcd(LL a, LL b, LL &x, LL &y){
    if (!b) return x = 1, y = 0, a;
    LL res = extgcd(b, a%b, y, x);
    return y -= a / b * x, res;
}
LL modInv(LL a, LL m){
    LL x, y, d = extgcd(a, m, x, y);
    return d == 1 ? (x + m) % m : -1;
}
LL BSGS(LL B, LL N, LL P) { //  B^L = N mod 
    map<LL, int> R;
    LL sq = (LL)(sqrt(P) + 1e-6), t = 1;
    for (int i = 0 ; i < sq ; i++) {
        if (t == N) return i;
        if (!R.count(t)) R[t] = i;
        t = (t * B) % P;
    }
    
    LL f = modInv(t, P);
    for (int i = 0 ; i <= sq + 1 ; i++) {
        if (R.count(N)) return i * sq + R[N];
        N = (N * f) % P;
    }
    return -1;
}
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int a, b, n; while (cin >> n >> a >> b) {
        LL L = BSGS(a, b, n);
        if (L == -1) cout << "no solution\n";
        else cout << L << '\n';
    }
}
