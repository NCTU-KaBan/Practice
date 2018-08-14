#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, q; cin >> n >> q;
        vector<int> data; data.push_back(0);
        for (int i = 0 ; i < n ; i++) {
            int p; cin >> p;
            data.push_back(p);
        }
        sort(data.begin(), data.end());
        while (q--) {
            int p; cin >> p;
            cout << *(--lower_bound(data.begin(), data.end(), p)) << (q == 0 ? '\n' : ' ');
        }
    }
}
