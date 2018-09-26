#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        LL n, g, l; cin >> n >> g >> l;
        vector<LL> data(n);
        for (auto &_data : data) cin >> _data;
        LL ans = 0, newG = 0;
        for (auto &_data : data) {
            if (_data % g != 0 || l % _data != 0) ans++, _data = -1;
            else {
                newG = __gcd(newG, _data);
            }
        }
        if (ans >= 2) {
            cout << ans << '\n';
            continue;
        }
        LL newL = 1;
        for (auto &_data : data)
            if (~_data) newL *= _data / newG;
        
        // newG, newL
        

    }
}
