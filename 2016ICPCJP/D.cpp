#include <bits/stdc++.h>
using namespace std;
struct State {
    int cnt[26];
    State() {
        for (int i = 0 ; i < 26 ; i++) cnt[i] = 0;
    }
    bool operator < (const State &rhs) const {
        for (int i = 0 ; i < 26 ; i++) {
            if (cnt[i] == rhs.cnt[i]) continue;
            return cnt[i] < rhs.cnt[i];
        }
        return false;
    }
    bool operator == (const State &rhs) const {
        for (int i = 0 ; i < 26 ; i++) {
            if (cnt[i] == rhs.cnt[i]) continue;
            return false;
        }
        return true;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, t; cin >> s >> t;
    int minLen = min(s.size(), t.size());
    int ans = 0;
    for (int l = 1 ; l <= minLen ; l++) {
        set<State> app;
        State cur;
        for (int i = 0 ; i < l - 1 ; i++) cur.cnt[s[i] - 'a']++;
        for (int i = 0 ; i + l <= (int)s.size() ; i++) {
            cur.cnt[s[l + i - 1] - 'a']++;
            app.insert(cur);
            cur.cnt[s[i]     - 'a']--;
        }
        State tar;
        for (int i = 0 ; i < l - 1 ; i++) tar.cnt[t[i] - 'a']++;
        for (int i = 0 ; i + l <= (int)t.size() ; i++) {
            tar.cnt[t[l + i - 1] - 'a']++;
            if (app.find(tar) != app.end()) ans = max(ans, l);
            tar.cnt[t[i]     - 'a']--;
        }
    }
    cout << ans << '\n';
}
