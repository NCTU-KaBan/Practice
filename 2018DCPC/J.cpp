#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int L[2], R[2], P[2], D[2];
        for (int i = 0 ; i < 2 ; i++)
            cin >> L[i] >> R[i] >> P[i] >> D[i];
        int K; cin >> K;
        int ans = 0;
        for (int i = 0 ; i < K ; i++) {
            if ((P[0] == R[0] && D[0] == 1) || (P[0] == L[0] && D[0] == 0)) D[0] = 1 - D[0];
            if ((P[1] == R[1] && D[1] == 1) || (P[1] == L[1] && D[1] == 0)) D[1] = 1 - D[1];
            if (D[0] == 0) P[0]--;
            else P[0]++;
            if (D[1] == 0) P[1]--;
            else P[1]++;
            if (P[0] == P[1]) ans++;
        }
        cout << ans << '\n';
    }
}
