#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    int n, q; LL s; 
    cin >> n >> q >> s;
    vector<LL> data;
    LL MIN = -9 * 1e18, MAX = 9 * 1e18;
    data.push_back(MIN);
    data.push_back(MAX);
    for (int i = 0 ; i < n ; i++) {
        LL input; cin >> input;
        data.push_back(input);
    }
    sort(data.begin(), data.end());
    while (q--) {
        LL input; cin >> input;
        int L = 0, R = data.size();
        while (R - L > 1) {
            int M = (R + L) >> 1;
            if (data[M] < input) L = M;
            else R = M;
        }
        if (abs(data[L] - input) <= s || abs(data[R] - input) <= s)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}
