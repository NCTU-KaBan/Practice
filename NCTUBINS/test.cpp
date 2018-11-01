#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        long long ans = -1;
        vector<long long> data(n);
        for (int i = 0 ; i < n; i++)
            cin >> data[i];
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0; j < n ; j++) {
                for (int k = 0 ; k < n ; k++) {
                    if (i == j || j == k || k == i) continue;
                    ans = max(ans, (data[i] + data[j]) ^ data[k]);
                }
            }
        }
        cout << ans << '\n';
    }
}
