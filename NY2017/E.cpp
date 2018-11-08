#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
const int INF = 0x3f3f3f3f;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int idx; cin >> idx; cout << idx << ' ';
        int n; cin >> n;
        double target; cin >> target;
        int p = 0, q = n / 2;
        int ans_p = -1, ans_q = -1;
        double minV = INF;
        while (p <= n && q <= n) {
            double cur = (double)p / q;
            double diff = abs(cur - target);
            if (diff < (double)minV) {
                minV = diff;
                ans_p = p;
                ans_q = q;
            }
            if (cur < target) {
                p++;
            } else {
                q++;
            }
        }
        int g = __gcd(ans_p, ans_q);
        cout << ans_p / g << '/' << ans_q / g << '\n';
    }
}
