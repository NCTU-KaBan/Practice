#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<int, int> pii;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<long long> data(n);
        for (auto &num : data) cin >> num;
        vector<pii> sum[35];
        int maxV = -1;
        for (int i = 0 ; i < n ; i++) {
            for (int j = i + 1 ; j < n ; j++) {
                long long number = data[i] + data[j];
                sum[__lg(number) + 1].push_back({i, j});
                maxV = max(maxV, (int)__lg(number) + 1);
            }
        }
        long long ans = -1;
        for (int i = 0 ; i < sum[maxV].size() ; i++) {
            for (int j = 0 ; j < n ; j++) {
                if (j == sum[maxV][i].F || j == sum[maxV][i].S) continue;
                ans = max(ans, (data[sum[maxV][i].F] + data[sum[maxV][i].S]) ^ data[j]);
            }
        }
        vector<int> mono[35];
        for (int i = 0 ; i < n ; i++) {
			mono[__lg(data[i]) + 1].push_back(i);
        }
        for (int x = 0 ; x < mono[maxV].size() ; x++) {
            for (int i = 0 ; i < n ; i++) {
                for (int j = i + 1 ; j < n ; j++) {
                    if (i == mono[maxV][x] || j == mono[maxV][x]) continue;
                    ans = max(ans, (data[i] + data[j]) ^ data[mono[maxV][x]]);
                }
            }
        }
        cout << ans << '\n';
    }
}
