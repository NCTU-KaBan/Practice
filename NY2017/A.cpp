#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int tmp; cin >> tmp;
        cout << tmp << ' ';
        long long n; cin >> n;
        cout << n * (n + 1) / 2 + n << '\n';
    }
}
