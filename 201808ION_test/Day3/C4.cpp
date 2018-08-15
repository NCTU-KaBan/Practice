#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 505;
const double EPS = 1e-8;
int main() {
    int t; cin >> t; while (t--) {
        string a, b; cin >> a >> b;
        int LCS[MAXLEN][MAXLEN]; memset(LCS, 0, sizeof(LCS));
        for (int i = 0 ; i < a.size() ; i++) {
            for (int j = 0 ; j < b.size() ; j++) {
                if (a[i] == b[j]) {
                    LCS[i + 1][j + 1] = LCS[i][j] + 1;
                } else {
                    LCS[i + 1][j + 1] = max(LCS[i + 1][j], LCS[i][j + 1]);
                }
            }
        }
        int ans = LCS[a.size()][b.size()];
        double LCS_E[MAXLEN][MAXLEN]; memset(LCS_E, 0, sizeof(LCS_E));
        for (int i = 0 ; i < a.size() ; i++) {
            for (int j = 0 ; j < b.size() ; j++) {
                if (a[i] == b[j]) {
                    LCS_E[i + 1][j + 1] = LCS_E[i][j] + 1;
                } else {
                    LCS_E[i + 1][j + 1] = (LCS_E[i + 1][j] + LCS_E[i][j + 1]) / 2.0;
                }
            }
        }
        double ans_E = LCS_E[a.size()][b.size()] + EPS;
        if (ans == 0) cout << 100 << '\n';
        else cout << (int)(100 * ans_E / ans) << '\n';
    }
}
