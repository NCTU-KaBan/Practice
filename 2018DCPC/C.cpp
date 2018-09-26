#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        string s, t; cin >> s >> t;
        bool conti = false;
        for (int i = 0 ; i <= s.size() / 2 ; i++) {
            if (min(s[i], s[s.size() - 1 - i]) != min(t[i], t[t.size() - 1 - i])
             || max(s[i], s[s.size() - 1 - i]) != max(t[i], t[t.size() - 1 - i])) {
                cout << -1 << '\n';
                conti = true;
                break;
            }
        }
        if (conti) continue;

        bool flag = false; int cnt = 0;
        for (int i = 0 ; i < s.size() / 2 ; i++) {
            if (s[i] == s[s.size() - 1 - i]) continue;
            if (flag) {
                if (s[i] != t[t.size() - i - 1]) {
                    cnt++;
                    flag ^= 1;
                }
            } else {
                if (s[i] != t[i]) {
                    cnt++;
                    flag ^= 1;
                }
            }
        }
        cout << cnt << '\n';
    }
}
