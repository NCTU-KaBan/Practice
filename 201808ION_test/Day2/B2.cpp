#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
bool check(vector<LL> &data, LL M, LL k) {
    int sum = 0;
    for (int i = 0 ; i < data.size() ; i++) {
        if (k == 0) return false;
        if (sum + data[i] > M)
            sum = 0, i--, k--;
        else sum += data[i];
    }
    return true;
}
int main() {
    int t; cin >> t; while (t--) {
        LL n, k; cin >> n >> k;
        LL pre; cin >> pre;
        vector<LL> data;
        for (int i = 1 ; i < n ; i++) {
            LL cur; cin >> cur;
            data.push_back(cur - pre);
            pre = cur;
        }
        LL L = 0, R = 1e18;
        while (R - L > 1) {
            LL M = (R + L) >> 1;
            if (check(data, M, k))
                R = M;
            else 
                L = M;
        }
        cout << R << '\n';
    }
}
