#include <bits/stdc++.h>
using namespace std;

int c[100005];
map<int, int> s;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int b, n, e, B, N, E;
    cin >> b >> n >> e >> B >> N >> E;

    int m = (b + n + e) / 2;

    for (int i = 0; i < m; i ++) {cin >> c[i]; c[i] *= -1;}
    sort(c, c + m);

    int tmp; 
        
    tmp = min(b, e); s[B + E] += tmp; b -= tmp; e -= tmp;
    tmp = min(b, n); s[B + N] += tmp; b -= tmp; n -= tmp;
    tmp = min(n, e); s[N + E] += tmp; n -= tmp; e -= tmp;
    s[B * 2] += b / 2; s[N * 2] += n / 2; s[E * 2] += e / 2;

    int ans = 1e9;
    map<int, int>::iterator iter = s.begin();
    for (int i = 0; i < m; i ++) {
        while (!iter->second) iter ++;
        ans = min(ans, iter->first * (-c[i]));
        iter->second --;
    }

    cout << ans << '\n';

}
