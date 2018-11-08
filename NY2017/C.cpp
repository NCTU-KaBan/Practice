#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10;
int n, m;
int B[MAXN][MAXN];
int group[MAXN][MAXN];
vector<vector<bool> > used;
vector<int> sz;
bool solve(int i, int j) {
    if (i == n) return true;
    if (B[i][j] != 0) 
        return solve(i + (j + 1) / m, (j + 1) % m);
    for (int x = 1 ; x <= sz[group[i][j]] ; x++) {
        if (used[group[i][j]][x]) continue;
        bool legal = true;
        for (int dx = -1 ; dx <= 1 ; dx++) {
            for (int dy = -1 ; dy <= 1 ; dy++) {
                if (dx == 0 && dy == 0) continue;
                int n_x = i + dx, n_y = j + dy;
                if (n_x < 0 || n_x >= n || n_y < 0 || n_y >= m) continue;
                if (B[n_x][n_y] == x) legal = false;
            }
        }
        if (!legal) continue;
        used[group[i][j]][x] = true;
        B[i][j] = x;
        if (solve(i + (j + 1) / m, (j + 1) % m)) return true;
        used[group[i][j]][x] = false;
        B[i][j] = 0;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int idx; cin >> idx; cout << idx << '\n';
        cin >> n >> m;
        string s; getline(cin, s);
        for (int i = 0 ; i < n ; i++) {
            getline(cin, s);
            for (auto &c : s) 
                if (c == '-') 
                    c = '0';
            stringstream ss; ss << s;
            int index = 0;
            while (ss >> B[i][index++]);
        }


        int chk; cin >> chk;
        used.clear();
        used.resize(50, vector<bool>(50, false));
        sz.clear();
        for (int i = 0 ; i < chk ; i++) {
            int num; cin >> num;
            for (int j = 0 ; j < num ; j++) {
                cin >> s;
                int x = s[1] - '0';
                int y = s[3] - '0';
                x--, y--;
                group[x][y] = i;
            }
            sz.push_back(num);
        }
        for (int i = 0 ; i < n ;i ++) {
            for (int j = 0 ; j < m;  j++) {
                if (B[i][j] == 0) continue;
                used[group[i][j]][B[i][j]] = true;
            }
        }
        solve(0, 0);
        
        for (int i = 0 ; i < n;  i++)
            for (int j = 0 ; j < m ; j++) 
                cout << B[i][j] << (j == m - 1 ? '\n' : ' ');
    }
}
