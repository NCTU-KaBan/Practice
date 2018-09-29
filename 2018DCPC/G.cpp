#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        LL n, g, l; cin >> n >> g >> l;
        vector<LL> data(n);
        for (auto &_data : data) cin >> _data;
        if (n == 1 && x != y) {
            cout << -1 << '\n';
            continue;
        }
        if (y % x) {
            cout << -1 << '\n';
            continue;
        }
        LL ans = 0, newG = 0;
        for (auto &_data : data) {
            if (_data % g || l % _data ) ans++;
            else {
                newG = __gcd(newG, _data);
                newL = newL * _data / __gcd(newL, _data);
            }
        }
        if (ans >= 2) {
            cout << ans << '\n';
            continue;
        }
        if (ans == 1) {

        }
        LL newL = 1;
        for (auto &_data : data)
            if (~_data) newL *= _data / newG;
        
        // newG, newL
        

    }
}
