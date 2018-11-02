#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<long long, long long> pii;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<pii> data(n);
        for (auto &p : data)
            cin >> p.F >> p.S;
        if (n != 4) {
            cout << "NO\n";
            continue;
        }
        sort(data.begin(), data.end());
        long long d = (data[0].F - data[1].F) * (data[0].F - data[1].F) + (data[0].S - data[1].S) * (data[0].S - data[1].S);
        vector<pii> vec;
        vec.push_back({data[0].F - data[1].F, data[0].S - data[1].S});
        vec.push_back({data[0].F - data[2].F, data[0].S - data[2].S});
        vec.push_back({data[1].F - data[3].F, data[1].S - data[3].S});
        vec.push_back({data[2].F - data[3].F, data[2].S - data[3].S});
        bool legal = true;
        for (int i = 0 ; i < 4 ; i++) {
            for (int j = i + 1 ; j < 4 ; j++) {
                long long res = abs(vec[i].F * vec[j].F + vec[i].S * vec[j].S);
                if (res == d || res == 0) continue;
                legal = false;
            }
        }
        if (legal) cout << "YES\n";
        else cout << "NO\n";
    }
}
