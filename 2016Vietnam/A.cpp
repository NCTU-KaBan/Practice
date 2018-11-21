#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        vector<LL> data;
        for (int i = 0 ; i < n ; i++) {
            LL num; cin >> num;
            data.push_back(num);
        }
        int L = 0, R = 0;
        LL sum = 0; bool used = false;
        LL ans = 0;
        while (R < n) {
            R++; sum += data[R - 1];
            if (data[R - 1] < m) {
                L = R;
                sum = 0;
                used = false;
            } else if (data[R - 1] == m){
                if (!used) {
                    used = true;
                } else {
                    while (1) {
                        sum -= data[L];
                        if (data[L] == m) {
                            L++;
                            break;
                        } else {
                            L++;
                        }
                    }
                }
            }
            if (used) ans = max(ans, sum);
        }
        cout << ans << '\n';
    }
}
