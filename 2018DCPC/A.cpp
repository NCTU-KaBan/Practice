#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        long long R, r; cin >> R >> r;
        if (R * R > 2 * r * r) cout << "1\n";
        else cout << "2\n";
    }
}
