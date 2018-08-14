#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MAX = 2e18 + 5;
int main() {
    int t; cin >> t; while (t--) {
        int n; cin >> n; vector<pair<LL, LL> > data;
        for (int i = 0 ; i < n ; i++) {
            LL a, b; cin >> a >> b;
            data.push_back(make_pair(a, b));
        }
        LL L = -MAX, R = MAX;
        for (auto p : data) {
            if (p.first == 0) continue;
            if (p.first < 0) {
                L = max(L, (MAX - p.second) / p.first);
                R = min(R, (0   - p.second) / p.first);
            } else {
                L = max(L, (0   - p.second) / p.first);
                R = min(R, (MAX - p.second) / p.first);
            }
        }
        while (R - L > 2) {
            LL M = (R + L) / 2, MM = (M + R) / 2;
            LL vM = 0, vMM = 0;
            for (auto p : data) {
                vM  = max(vM,  p.first * M  + p.second);
                vMM = max(vMM, p.first * MM + p.second);
            }
            if (vM < vMM) R = MM;
            else L = M;
        }
        LL vL = 0, vR = 0, vM = 0;
        for (auto p : data) {
            vL = max(vL, p.first * L + p.second);
            vR = max(vR, p.first * R + p.second);
            vM = max(vM, p.first * (L + R) / 2 + p.second);
        }
        cout << min({vL, vR, vM}) << '\n';
    }
}
