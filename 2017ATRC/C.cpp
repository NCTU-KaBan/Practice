#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1e5 + 5;
int main() {
    int n, t; cin >> n >> t;
    LL data[MAXN], maxV[MAXN];
    memset(maxV, 0, sizeof(maxV));
    for (int i = 0 ; i < n ; i++)
        cin >> data[i];
    maxV[0] = data[0];
    for (int i = 1 ; i < n ; i++) {
        maxV[i] = max(maxV[i - 1], data[i]);
        data[i] += data[i - 1];
    }
    for (int i = 0 ; i < n ; i++) {
        if (t < data[i]) cout << 1 << '\n';
        else cout << (t - data[i]) / maxV[i] + 2 << '\n';
    }

}

