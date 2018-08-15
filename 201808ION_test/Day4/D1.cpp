#include <bits/stdc++.h>
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
int main() {
    int t; cin >> t; while (t--) {
        LL a, b, m; cin >> a >> b >> m;
        if (modInv(b, m) == -1) {
            cout << "SeaCow\n";
        } else {
            cout << a * modInv(b, m) % m << '\n';
        }
    }
}
