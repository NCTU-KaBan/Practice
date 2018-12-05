#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
const int MAXN = 20;
bool used[MAXN];
int n;
map<pii, int> cnt;
vector<pii> data;
LL ans;
void solve(int pairNumber) {
    if (pairNumber * 2 == n) {
        LL sum = 0;
        for (auto &p : cnt) {
            // cout << "(" << p.first.first << ' ' << p.first.second << ' ' << p.second << ") ";
            int target = p.second;
            sum += target * (target - 1) / 2;
        }
        // cout << '\n';
        ans = max(sum, ans);
        return ;
    }
    int idx = -1;
    for (int i = 0 ; i < n ; i++) {
        if (used[i]) continue;
        idx = i; used[i] = true; break;
    }
    for (int i = idx + 1 ; i < n ; i++) {
        if (used[i]) continue;
        used[i] = true;
        pii m = make_pair(data[idx].first - data[i].first, data[idx].second - data[i].second);
        if (m.first < 0) m.first *= -1, m.second *= -1;
        if (m.first == 0) m.second = abs(m.second);
        int g = __gcd(abs(m.first), abs(m.second));
        m.first /= g;
        m.second /= g;
        cnt[m]++;
        solve(pairNumber + 1);
        used[i] = false;
        cnt[m]--;
        if (cnt[m] == 0) cnt.erase(m);
    }
    used[idx] = false;
    return ;
}
int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    ans = 0;
    cin >> n; data.resize(n);
    for (auto &p : data)
        cin >> p.first >> p.second;
    memset(used, false, sizeof(used));
    solve(0);
    cout << ans << '\n';
}
