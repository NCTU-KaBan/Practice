#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long uLL;
const int MAXN = 40010;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    vector<bool> isP(MAXN, true);
    vector<int> P;
    isP[0] = isP[1] = false;
    for (int i = 2 ; i < MAXN ; i++) {
        if (isP[i]) P.push_back(i);
        for (auto p : P) {
            if (i * p >= MAXN) break;
            isP[i * p] = false;
            if (i % p == 0) break;
        }
    }
    int t; cin >> t; while (t--) {
        int n, tn; cin >> n; tn = n;
        uLL x = 1, y = 1;
        for (auto p : P) {
            uLL tt = 1, add = 1, cnt = 1;
            if (n == 0) break;
            while (n % p == 0) {
                add = add * p * p;
                tt += add;
                cnt++;
                n /= p;
            }
            x *= tt;
            y *= cnt;
        }
        if (n > 1) {
            x *= (1 + 1LLU * n * n);
            y *= 2;
        }
        cout << x - y * tn << '\n';
    }
}
