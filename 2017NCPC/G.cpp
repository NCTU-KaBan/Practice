#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
const int MAXN = 1e5 + 5;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        pair<int, int> data[MAXN];
        set<pair<int, int> > r;
        for (int i = 0 ; i < m ; i++) {
            int num, pen; cin >> num >> pen;
            if (num == 1) { 
                data[0].F--, data[0].S += pen;
                cout << r.lower_bound(data[0]) - r.begin() << '\n';
            } else {
                r.erase(r.find(data[num]));
                data[num].F--; data[num].S += pen;
                r.insert(data[num]);
                cout << r.lower_bound(data[0]) - r.begin() << '\n';
            }
        }
    }
}
