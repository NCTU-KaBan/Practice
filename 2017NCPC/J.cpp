#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int l, r; while (cin >> l >> r) {
        if (l == 0 && r == 0) {
            cout << "Not a moose\n";
        } else if (l == r) {
            cout << "Even " << 2 * l << '\n';
        } else {
            cout << "Odd " << 2 * max(l, r) << '\n';
        }
    }
}
