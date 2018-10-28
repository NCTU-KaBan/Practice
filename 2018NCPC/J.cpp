#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL INF = 0x3f3f3f3f3f3f3f3f;

string solve(LL m, LL n, LL c) {
    string s = "";
    for (LL i = 0; i < m; i ++) s += "0";
    for (LL i = 0; i < n; i ++) s += "1";
    
    LL cur = m;
    while (c) {
        if (c > m) {
            char tmp = s[cur]; s[cur] = s[cur - m]; s[cur - m] = tmp;
            cur ++;
            c -= m;
        } else {
            char tmp = s[cur]; s[cur] = s[cur - c]; s[cur - c] = tmp;
            break;
        }
    }
    return s;
}

LL check(LL m, LL n, LL total) {
    return (m + n) * (m + n - 1) / 2 == total;
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(0);
    LL a, b, c, d, total;
    cin >> a >> b >> c >> d;
    total = a + b + c + d;

    LL m = INF, n = INF;
    for (LL i = 1; i < 100000; i ++) {
        if (i * (i - 1) / 2 == a) m = i;
        if (i * (i - 1) / 2 == d) n = i;
    }

    if (m == INF || n == INF) {
        cout << "impossible\n";
        return 0;
    }

    if (check(m, n, total)) {
        cout << solve(m, n, c) << '\n';
        return 0;
    }

    if (m == 1 && b == 0 && c == 0) {
        //if (check(0, n, total)) {
            string s;
            for (LL i = 0; i < n; i ++)
                s += "1";
            cout << s << '\n';
            return 0;
        //}
    }

    if (n == 1 && b == 0 && c == 0) {
        //if (check(m, 0, total)) {
            string s;
            for (LL i = 0; i < m; i ++)
                s += "0";
            cout << s << '\n';
            return 0;
        //}
    }

    cout << "impossible\n";
}
