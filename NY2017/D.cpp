#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MAX 10000

struct obj {
    LL x = 0, a = 0, b = 0, c = 0;
};
vector<obj> dp(MAX);

obj solve(int n) {
    if (dp[n].x) return dp[n];
    obj tmp = solve(n - 1);
    dp[n].x += 2 * tmp.x;
    dp[n].a += 2 * tmp.x + 2 * tmp.a;
    dp[n].b += 1 * tmp.x + 2 * tmp.b;
    dp[n].c += 0 * tmp.x + 2 * tmp.c;

    tmp = solve(n - 2);
    dp[n].x += 7 * tmp.x;
    dp[n].a += 8 * tmp.x + 7 * tmp.a;
    dp[n].b += 4 * tmp.x + 7 * tmp.b;
    dp[n].c += 4 * tmp.x + 7 * tmp.c;
    
    for (int i = 3; i < n; i ++) {
        tmp = solve(n - i);
        dp[n].x += 8 * tmp.x;
        dp[n].a += 8 * tmp.x + 8 * tmp.a;
        dp[n].b += ((i - 2) * 8) * tmp.x + 8 * tmp.b;
        dp[n].c += 8 * tmp.x + 8 * tmp.c;
    }
    dp[n].x += 8;
    dp[n].a += 8;
    dp[n].b += (n - 2) * 8;
    dp[n].c += 8;
    return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    dp[0].x = 1; dp[0].a = 0; dp[0].b = 0; dp[0].c = 0;
    dp[1].x = 2; dp[1].a = 2; dp[1].b = 1; dp[1].c = 0;
    dp[2].x = 11; dp[2].a = 16; dp[2].b = 8; dp[2].c = 4;
    int T, num, n; cin >> T; for(int t = 1; t <= T; t ++) {
        cin >> num >> n;
        obj ans = solve(n);
        cout << t << ' ' << ans.x << ' ' << ans.a << ' ' << ans.b << ' ' << ans.c  << '\n';
    }
}
