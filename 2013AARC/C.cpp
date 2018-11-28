#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long LL;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int trans(char c) {
    if (c == 'R') return 0;
    if (c == 'D') return 1;
    if (c == 'L') return 2;
    if (c == 'U') return 3;
    return -1;
}
struct State {
    bool ok[4]; // R, D, L, U
    bool vis;
    State() {
        memset(ok, true, sizeof(ok));
        vis = false;
    }
};
struct R {
    int l, t, r, b;
};
typedef pair<int, int> pii;
const int MAXN = 300 + 5;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; while (cin >> n && n) {
        vector<R> data(n);
        vector<int> x, y;
        for (auto &Rect : data) {
            cin >> Rect.l >> Rect.t >> Rect.r >> Rect.b;
            Rect.t *= -1;
            Rect.b *= -1;
            swap(Rect.t, Rect.l);
            swap(Rect.b, Rect.r);
            x.push_back(Rect.l); x.push_back(Rect.r);
            y.push_back(Rect.t); y.push_back(Rect.b);
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        y.erase(unique(y.begin(), y.end()), y.end());
        State G[MAXN][MAXN];
        for (auto &Rect : data) {
            int L, R, T, B;
            T = lower_bound(y.begin(), y.end(), Rect.t) - y.begin();
            B = lower_bound(y.begin(), y.end(), Rect.b) - y.begin();
            L = lower_bound(x.begin(), x.end(), Rect.l) - x.begin();
            R = lower_bound(x.begin(), x.end(), Rect.r) - x.begin();
            for (int i = T + 1 ; i <= B ; i++) { // Vertical
                G[i][L].ok[trans('R')] = false;
                G[i][L + 1].ok[trans('L')] = false;
                G[i][R].ok[trans('R')] = false;
                G[i][R + 1].ok[trans('L')] = false;
            }
            for (int j = L + 1 ; j <= R ; j++) { // Horizontal
                G[T][j].ok[trans('D')] = false;
                G[T + 1][j].ok[trans('U')] = false;
                G[B][j].ok[trans('D')] = false;
                G[B + 1][j].ok[trans('U')] = false;
            }
        }   
        int H = 300, W = 300;
        /*
        cout << H << ' ' << W << '\n';
        for (int i = 0 ; i < H ; i++) {
            for (int j = 0 ; j < W ; j++) {
                cout << ' ';
                if (!G[i][j].ok[trans('U')]) cout << '-';
                else cout << ' ';
            }
            cout << '\n';
            for (int j = 0 ; j < W ; j++)  {
                if (!G[i][j].ok[trans('L')]) cout << '|';
                else cout << ' ';
                cout << ' ';
            }
            if (!G[i][y.size()].ok[trans('R')]) cout << '|';
            else cout << ' ';
            cout << '\n';
        }
        cout << '\n';
        */
        int ans = 0;
        for (int i = 0 ; i < H ; i++) {
            for (int j = 0 ; j < W ; j++) {
                if (G[i][j].vis) continue;
                G[i][j].vis = true; ans++;
                queue<pii> q; q.push({i, j}); 
                while (q.size()) {
                    pii p = q.front(); q.pop();
                    for (int d = 0 ; d < 4 ; d++){
                        pii next = make_pair(p.F + dx[d], p.S + dy[d]);
                        if (next.F < 0 || next.F > H || next.S < 0 || next.S > W) continue;
                        if (!G[p.F][p.S].ok[d]) continue;
                        if (G[next.F][next.S].vis) continue;
                        G[next.F][next.S].vis = true;
                        q.push(next);
                    }
                }
                /*
                for (int X = 0 ; X <= x.size() ; X++) {
                    for (int Y = 0 ; Y <= y.size() ; Y++) {
                        cout << G[X][Y].vis << ' ';
                    }
                    cout << '\n';
                }
                */
            }
        }
        cout << ans << '\n';
    }
}
