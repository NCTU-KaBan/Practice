#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 2e5 + 5;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<pii> data(n);
    for (auto &p : data) cin >> p.first >> p.second;
    map<int, int> line;
    int st[MAXN], en[MAXN];
    memset(st, 0, sizeof(st));
    memset(en, 0, sizeof(en));
    for (auto &p : data) {
        line[p.first]++;
        line[p.second]--;
        st[p.first]++;
        en[p.second]++;
    }
    for (int i = 1 ; i < MAXN ; i++) {
        st[i] += st[i - 1];
        en[i] += en[i - 1];
    }

    int ans[2] = {0};
    for (int i = 0 ; i < n ; i++)
        ans[0] = max(ans[0], st[data[i].second - 1] - en[data[i].first]);

    int sum = 0;
    for (auto &p : line) {
        sum += p.second;
        ans[1] = max(ans[1], sum);
    }
    cout << ans[0] << ' ' << ans[1] << '\n';

}
