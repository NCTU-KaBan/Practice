#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
vector<LL> val;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        LL p; cin >> p;
        vector<LL> data(10);
        val.resize(10);
        for (int i = 0 ; i < 10 ; i++) cin >> data[i];
        val[0] = 1, val[1] = 5, val[2] = 10;
        val[3] = 20, val[4] = 50, val[5] = 100;
        val[6] = 200, val[7] = 500, val[8] = 1000;
        val[9] = 2000;
        LL total = 0; 
        for (int i = 0 ; i < 10 ; i++)
            total += val[i] * data[i];
        if (total - p < 0) {
            cout << -1 << '\n';
            continue;
        }
        if (total == 0) {
            cout << 0 << '\n';
            continue;
        }
        LL total_coin = 0;
        for (int i = 0 ; i < 10 ; i++)
            total_coin += data[i];

        LL target = total - p;

    }
}
