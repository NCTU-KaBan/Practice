#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15;
int table[MAXN][MAXN];
char SSN(string x) {
    int ret = 0;
    for (int i = 0 ; i < 4 ; i++)
        ret = table[ret][x[i] - '0'];
    return ret + '0';
}
bool check(string x) {
    int ret = SSN(x.substr(0, 4)) - '0';
    return table[ret][x[4] - '0'] == 0;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    for (int i = 0 ; i < 10 ; i++)
        for (int j = 0 ; j < 10 ; j++)
            cin >> table[i][j];
    int ans = 0;
    for (int i = 0 ; i < 10000 ; i++) {
        stringstream ss; ss << i;
        string target, cur; ss >> cur;
        while (cur.size() != 4) cur = '0' + cur;
        bool legal = true;
        for (int x = 0 ; x < 5 && legal ; x++) {
            for (int y = 0 ; y < 10 && legal ; y++) {
                target = cur + SSN(cur);
                if (target[x] == y + '0') continue;
                target[x] = y + '0';
                if (!check(target)) continue;
                ans++;
                legal = false;
            }
        }
        for (int x = 0 ; x < 4 && legal ; x++) {
            target = cur + SSN(cur);
            swap(target[x], target[x + 1]);
            if (target == cur + SSN(cur)) continue;
            if (!check(target)) continue;
            ans++;
            legal = false;
        }
    }
    cout << ans << '\n';

}
