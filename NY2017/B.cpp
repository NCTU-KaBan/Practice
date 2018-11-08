#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int tmp; cin >> tmp;
        cout << tmp << ' ';
        long long ans = 0;
        long long b; cin >> b;
        long long target; cin >> target;
        while (target) {
            ans += (target % b) * (target % b);
            target /= b;
        }
        cout << ans << '\n';
    }
}
