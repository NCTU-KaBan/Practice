#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    s = "R" + s;
    vector<int> ans;
    int L_cnt = 0;
    int cur = 0;
    for (int i = 0 ; i < s.size() ; i++) {
        if (s[i] == 'R') {
            int cnt = 0;
            for (int j = i + 1 ;; j++) {
                if (s[j] == 'L') cnt++;
                else break;
            }
            cur += cnt + 1 + L_cnt;
            L_cnt = cnt;
        } else {
            cur--;
        }
        ans.push_back(cur);
    }
    for (int i = 0 ; i < ans.size() ; i++)
        cout << ans[i] << '\n';
}
