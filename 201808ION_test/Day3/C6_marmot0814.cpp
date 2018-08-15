#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL pow10(LL n) {
    LL ret = 1;
    for (int i = 0 ; i < n ; i++)
        ret *= 10;
    return ret;
}
LL F(LL n) {
    return 45 * n * pow10(n - 1);
}
LL PartialF(LL x, LL n) {
    return F(n) * (x + 1) + x * (x + 1) / 2 * pow10(n);
}
LL solve(LL target) {
    LL ret = 0, num_of_nine = 0;
    while (target >= 0) {
        LL last_bit  = target % 10;
        LL target_sum = 0, tmp = target / 10;
        while (tmp > 0) target_sum += tmp % 10, tmp /= 10;
        ret += target_sum * (last_bit + 1) * pow10(num_of_nine);
        ret += PartialF(last_bit, num_of_nine);
        target /= 10;
        target--;
        num_of_nine++;
    }
    return ret;
}
int main() {
    int T; cin >> T; while (T--) {
        LL s, t; cin >> s >> t;
        cout << solve(t) - solve(s - 1) << '\n';
    }
}
