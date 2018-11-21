#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> data;
    for (int i = 0 ; i < q ; i++) {
        int num; cin >> num;
        data.push_back(num);
    }
    vector<bool> used(n + 5, false);
    reverse(data.begin(), data.end());
    for (auto num : data) {
        if (used[num]) continue;
        used[num] = true;
        cout << num << '\n';
    }
    for (int i = 1 ; i <= n ; i++) {
        if (used[i]) continue;
        cout << i << '\n';
    }
}
