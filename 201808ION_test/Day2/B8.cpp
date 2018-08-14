#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    int t; cin >> t; while (t--) {
        priority_queue<LL, vector<LL>, greater<LL> > pq;
        int n; cin >> n; for (int i = 0 ; i < n ; i++) {
            LL input; cin >> input;
            pq.push(input);
        }
        LL ans = 0;
        while (pq.size() != 1) {
            LL F = pq.top(); pq.pop();
            LL S = pq.top(); pq.pop();
            ans += F + S;
            pq.push(F + S);
        }
        cout << ans << '\n';
    }
}
