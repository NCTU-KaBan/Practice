/*
   ans[1] = (b^2 - 4ac) / 4a^2
*/
#include <bits/stdc++.h>
using namespace std;
struct F{
    int a, b;       // a / b;
    F() { a = 0, b = 1; trim(); }
    F(int _a, int _b) : a(_a), b(_b) { trim(); }
    void trim() {
        int g = __gcd(abs(a), abs(b)); a /= g, b /= g;
        if (b < 0) a *= -1, b *= -1;
    }
    friend ostream& operator << (ostream& out, const F& f) {
        out << f.a << "/" << f.b;
        return out;
    }
};
int main() {
    int t; cin >> t; while (t--) {
        int data[4]; for (int i = 0 ; i < 4 ; i++) cin >> data[i];
        data[2] -= data[3];
        F ans[2];
        ans[0] = F(- data[1], 2 * data[0]);
        ans[1] = F( data[1] * data[1] - 4 * data[0] * data[2], 4 * data[0] * data[0]);
        cout << ans[0] << ' ' << ans[1] << '\n';
    }
}
