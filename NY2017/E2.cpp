#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int idx; cin >> idx; cout << idx << ' ';
        int n; cin >> n;
        double target; cin >> target;
        double minV = INF;
        int ans_p = -1, ans_q = -1;
        for (int q = max(1, (int)sqrt(n) - 5) ; q <= n ; q++) {
            int cur = q * target;
            double diff = (double)cur / q;
            if (abs(diff - target) < minV) {
                minV = abs(diff - target);
                ans_p = cur;
                ans_q = q;
            }
            diff = (double)(cur + 1) / q;
            if (abs(diff - target) < minV) {
                minV = abs(diff - target);
                ans_p = cur + 1;
                ans_q = q;
            }
        }
        int g = __gcd(ans_p, ans_q);
        cout << ans_p / g << '/' << ans_q / g << '\n';
    }
}
