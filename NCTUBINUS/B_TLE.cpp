#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t; while (t--) {
        unsigned long long n; cin >> n;
        unsigned long long ans = 0;
        for (unsigned long long i = 1 ; i * (i + 1) <= n ; i++) {
            if ((n - i * (i + 1)) % i != 0) continue;
            unsigned long long regis = (n - i * (i + 1)) / i + 1;
            ans += regis * regis;
        }
        cout << ans << '\n';
    }
}
