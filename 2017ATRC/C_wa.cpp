#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, t;
    cin >> n >> t;
    int T = t;
    int s[100005];
    const int INF = 0x3f3f3f3f;

    for (int i = 0; i < n; i ++)
        cin >> s[i];
    int state;
    int item = INF, left = 0, mod = 0, cur = s[0];
    for (int i = 0; i < n; i ++) {
        if (item == 1) {
            cout << item << '\n';
            continue;
        }
        if (i) t -= s[i - 1];
        // cout << "t/s= " << t / s[i] + 1 << " item=" << item << '\n';
        double x = cur * cur / (cur - (double)s[i]);
        cout << "x= " << x << "cur= " << cur << '\n';
        if (i == 0 || t / (double)cur - (t) / (double)s[i] < 1 || x < 0) {
            item = t / s[i];
            left = t % s[i];
            item ++;
            mod = s[i];
            // cout << "left= " << left << '\n';
            cout << item << "x" << '\n';
            state = 1;
            cur = s[i];
            continue;
        }

        // cout << "OK\n";
        
        // mod = max(mod, s[i]);

        if (left < s[i]) {
            left += mod;
            item --;
        }

        //cout << "left= " << left << " mod=" << mod << '\n';
        
        //if (left == s[i]) left += mod;
        state = 0;
        left -= s[i];
        cout << item << '\n';
    }
}
