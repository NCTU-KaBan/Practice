#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5000;
typedef long long LL;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    LL ans[MAXN]; memset(ans, 0, sizeof(ans));
    LL base[MAXN]; 
    LL dp[MAXN];
    base[0] = 1; base[1] = 2; base[2] = 7;
    for (int i = 3 ; i < MAXN ; i++)
        base[i] = 8;
    ans[0] = 1; ans[1] = 2;
    for (int x = 2 ; x < MAXN ; x++) {
        
    }
    cout << dp[3] << '\n';
    int t; cin >> t; while (t--) {
        int idx; cin >> idx; cout << idx << ' ';
        int n; cin >> n;
        
    }
}
