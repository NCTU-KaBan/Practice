#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int P[500];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T, n; cin >> T; while (T --) {
        cin >> n;
        for (int i = 0; i < 3 * n; i ++)
            cin >> P[i];

        sort(P, P + 3 * n);
        
        int sum = 0;
        for (int i = n; i < 3 * n; i += 2)
            sum += P[i];

        cout << sum << '\n';
    }
}
