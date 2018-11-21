#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pii> data(m);
    for (auto &p : data) cin >> p.first >> p.second, p.second--;
    sort(data.begin(), data.end());
    vector<int> L(n), R(n);
    for (int i = 0 ; i < n ; i++) L[i] = R[i] = i;
    for (auto p : data) {
        int y = p.second;
        L[y + 1] = L[y];
        R[y] = R[y + 1];
    }
    for (int i = 0 ; i < n ; i++)
        cout << R[i] - L[i] + 1 << (i == n - 1 ? '\n' : ' ');
}
