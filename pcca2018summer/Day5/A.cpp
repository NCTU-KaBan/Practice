#include <bits/stdc++.h>
using namespace std;
bool G[8][8];
bool r[8], c[8], l1[15], l2[15];
bool solve(int cur) {
    if (cur == 8) return true;
    if (r[cur]) return solve(cur + 1);
    for (int i = 0 ; i < 8 ; i++) {
        if (c[i]) continue;
        if (l1[cur + i]) continue;
        if (l2[cur - i + 7]) continue;
        c[i] = l1[cur + i] = l2[cur - i + 7] = true;
        G[cur][i] = true;
        if (solve(cur + 1)) return true;
        c[i] = l1[cur + i] = l2[cur - i + 7] = false;
        G[cur][i] = false;
    }
    return false;
}
int main() {
    int n; cin >> n; 
    memset(G, 0, sizeof(G));
    memset(r, 0, sizeof(r));
    memset(c, 0, sizeof(c));
    memset(l1, 0, sizeof(l1));
    memset(l2, 0, sizeof(l2));
    for (int i = 0 ; i < n ; i++) {
        int x, y; cin >> x >> y;
        G[x][y] = true;
        r[x] = true;
        c[y] = true;
        l1[x + y] = true;
        l2[x - y + 7] = true;
    }
    solve(0);
    for (int i = 0 ; i < 8 ; i++) {
        for (int j = 0 ; j < 8 ; j++) {
            if (G[i][j])
                cout << 'Q';
            else 
                cout << '.';
        }
        cout << '\n';
    }
}
