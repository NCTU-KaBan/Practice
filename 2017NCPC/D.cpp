#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        int cnt[MAXN]; memset(cnt, 0, sizeof(cnt));
        for (int i = 0 ; i < n;  i++) {
            string s; cin >> s;
            for (int j = 0 ; j < m ; j++)
                if (s[j] == '1') cnt[j]++;
        }
        for (int i = 0 ; i < m ; i++) {
            if (cnt[i] * 2 < n) cout << 1;
            else cout << 0;
        }
        cout << '\n';
    }
}
