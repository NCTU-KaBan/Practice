#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int B[MAXN][MAXN], n;
bool R[MAXN][MAXN], C[MAXN][MAXN]; 
bool solve(int x, int y) {
    if (x == n) return true;
    if (B[x][y] != -1) {
        if (R[x][B[x][y]] || C[y][B[x][y]]) return false;
        R[x][B[x][y]] = true;
        C[y][B[x][y]] = true;
        return solve(x + (y + 1) / n, (y + 1) % n);
    } else {
        for (int i = 1 ; i <= n ; i++) {
            if (R[x][i] || C[y][i]) continue;
            B[x][y] = i;
            R[x][i] = true; C[y][i] = true;
            if (solve(x + (y + 1) / n, (y + 1) % n)) return true;
            R[x][i] = false; C[y][i] = false; B[x][y] = -1;
        }
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int k; cin >> n >> k;
    memset(B, -1, sizeof(B));
    memset(R, false, sizeof(R)); 
    memset(C, false, sizeof(C));
    for (int i = 0 ; i < k ; i++)
        for (int j = 0 ; j < n ; j++)
            cin >> B[i][j];
    if (solve(0, 0)) {
        cout << "yes\n";
        for (int i = 0 ; i < n ; i++)
            for (int j = 0 ; j < n ; j++)
                cout << B[i][j] << (j == n - 1 ? '\n' : ' ');
    } else {
        cout << "no\n";
    }
}
