#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t; while (t--) {
        int n, m, k; cin >> n >> m >> k;
        deque<int> deq;
        int ans = 0;
        for (int i = 0 ; i < n ; i++) {
            int input; cin >> input;
            while (deq.size() && input - deq.front() >= m) deq.pop_front();
            deq.push_back(input);
            while (deq.size() >= k) ans++, deq.pop_back();
        }
        cout << ans << '\n';

    }
}
