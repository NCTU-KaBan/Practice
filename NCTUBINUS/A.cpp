#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
vector<LL> val;
LL solve(LL target, vector<LL> &data) {
    LL sum = 0;
    for (int i = 9 ; i >= 0 ; i--) {
        if (i == 4 || i == 7) {
            sum += min((target / val[i] / 2 * 2), data[i] / 2 * 2);
            target -= min((target / val[i] / 2 * 2), data[i] / 2 * 2) * val[i];
        } else {
            sum += min(data[i], target / val[i]);
            target -= min(data[i], target / val[i]) * val[i];
        }
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
        sum = min(sum, solve(target, data));

        if (target >= 50 && data[4] != 0) {
            data[4]--;
            sum = min(sum, solve(target - 50, data) + 1);
            data[4]++;
        }
        if (target >= 500 && data[7] != 0) {
            data[7]--;
            sum = min(sum, solve(target - 500, data) + 1);
            data[7]++;
        }
        if (target >= 550 && data[7] != 0 && data[4] != 0) {
            data[4]--; data[7]--;
            sum = min(sum, solve(target - 550, data) + 2);
        }
        if (sum == INF) cout << -1 << '\n';
        else cout << total_coin - sum << '\n';
    }
}
