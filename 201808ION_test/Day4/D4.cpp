#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL f_pow(LL a, LL b, LL m) {
    if (b == 0) return 1ll;
    LL k = f_pow(a, b >> 1, m);
    if (b & 1) return k * k % m * a % m;
    else return k * k % m;
}
int main() {
    int t; cin >> t; while (t--) {
        LL a, b, m; cin >> a >> b >> m;
        cout << f_pow(a, b, m) << '\n';
    }
}
