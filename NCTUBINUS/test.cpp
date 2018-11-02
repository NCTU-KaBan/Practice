#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
vector<LL> val;
LL solve(LL target, vector<LL> &data) {
    LL sum = 0;
    for (int i = 9 ; i >= 0 ; i--) {
        if (i == 4 || i == 7) continue;
        sum += min(data[i], target / val[i]);
        target -= min(data[i], target / val[i]) * val[i];
    }
    if (target != 0) {
        return INF;
    } else {
        return sum;
    }
}
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
        if (total == p) {
            cout << 0 << '\n';
            continue;
        }
        LL total_coin = 0;
        for (int i = 0 ; i < 10 ; i++)
            total_coin += data[i];
        

        LL target = total - p;
        LL sum = INF;
        LL add_50  = data[4] / 2;
        LL add_500 = data[7] / 2;
        data[5] += add_50;
        data[8] += add_500;
        sum = min(sum, solve(target, data));
        data[5] -= add_50;
        data[8] -= add_500;

        if (target >= 50 && data[4] != 0) {
            target -= 50;
            LL add = (data[4] - 1) / 2;
            data[5] += add;
            sum = min(sum, solve(target, data) + 1);
            data[5] -= add;
            target += 50;
        }
        if (target >= 500 && data[7] != 0) {
            target -= 500;
            LL add = (data[7] - 1) / 2;
            data[8] += add;
            sum = min(sum, solve(target, data) + 1);
            data[8] -= add;
            target += 500;
        }
        if (target >= 550 && data[7] != 0 && data[4] != 0) {
            target -= 500 + 50;
            data[5] += (data[4] - 1) / 2;
            data[8] += (data[7] - 1) / 2;
            sum = min(sum, solve(target, data) + 2);
        }
        if (sum == INF) cout << -1 << '\n';
        else cout << total_coin - sum << '\n';
    }
}
