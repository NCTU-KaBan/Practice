#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int p, q; cin >> p >> q;
    int s; cin >> s;
    if (p * q / __gcd(p, q) <= s) cout << "yes\n";
    else cout<< "no\n";
}
