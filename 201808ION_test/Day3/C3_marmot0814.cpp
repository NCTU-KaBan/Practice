#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 5;
const int MAXM = 1e3 + 5;
const int MAXS = 1e4 + 5;
const int MAXW = 1e6 + 5;
int main() {
    int t; cin >> t; while (t--) {
        int n, m, s; cin >> n >> m >> s;
        int dp_cap[MAXS]; memset(dp_cap, 0, sizeof(dp_cap));
        for (int i = 0 ; i < n ; i++) {
            int con, cap; cin >> con >> cap;
            for (int j = MAXS - 1 ; j >= con ; j--) 
                dp_cap[j] = max(dp_cap[j], dp_cap[j - con] + cap);
        }
        int dp_val[MAXW]; memset(dp_val, 0, sizeof(dp_val));
        for (int i = 0 ; i < m ; i++) {
            int wei, val; cin >> wei >> val;
            for (int j = dp_cap[s] ; j >= wei ; j--) 
                dp_val[j] = max(dp_val[j], dp_val[j - wei] + val);
        }
        cout << dp_val[dp_cap[s]] << '\n';
    }
}
