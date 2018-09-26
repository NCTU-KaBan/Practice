#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MAXN = 1e3 + 5;
const LL MOD = 7901;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        long long fact[MAXN]; fact[0] = 1;
        for (int i = 1 ; i < MAXN ; i++)
            fact[i] = (fact[i - 1] * i) % MOD;
        map<int, int> cnt;
        for (int i = 0 ; i < n ; i++) {
            int data; cin >> data;
            cnt[data]++;
        }
        LL ans = 1;
        for (auto p : cnt) {
            ans *= fact[p.second];
            ans %= MOD;
        }
        cout << ans << '\n';
    }
}
