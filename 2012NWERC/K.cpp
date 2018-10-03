#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
typedef long long LL;
typedef map<string, int>::iterator ITER;
LL fact(int n) {
    if (n == 0) return 1;
    return fact(n - 1) * n;
}
int main() {
    int K; while (cin >> K) {
        string s[2]; cin >> s[0] >> s[1];
        string trans[2][MAXN];
        for (int i = 0 ; i < 2 ; i++)
            for (int j = 0 ; j < s[0].size() ; j += K)
                for (int k = 0 ; k < K ; k++)
                    trans[i][k] += s[i][j + k];
        map<string, int> m[2];
        for (int i = 0 ; i < 2 ; i++)
            for (int k = 0 ; k < K ; k++)
                m[i][trans[i][k]]++;
        if (m[0].size() != m[1].size()) {
            cout << 0 << '\n';
            continue;
        }
        ITER it[2];
        it[0] = m[0].begin(); it[1] = m[1].begin();
        bool legal = true; LL ans = 1;
        while (legal && it[0] != m[0].end() && it[1] != m[1].end()) {
            if (it[0]->first == it[1]->first && it[0]->second == it[1]->second) {
                ans *= fact(it[0]->second);
            } else legal = false;
            it[0]++, it[1]++;
        }
        if (legal) cout << ans << '\n';
        else cout << 0 << '\n';
    }
}
