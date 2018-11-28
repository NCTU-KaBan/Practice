#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Ant {
    int dir;
    int pos;
    int idx;
    bool operator < (const Ant &rhs) const {
        return pos == rhs.pos ? dir < rhs.dir : pos < rhs.pos;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, l; while (cin >> n >> l && (n || l)) {
        vector<Ant> data(n);
        int index = 1;
        for (auto &a : data) {
            string dir; cin >> dir;
            cin >> a.pos;
            a.dir = dir[0] == 'R' ? 1 : -1;
            a.idx = index++;
        }
        int cnt = 0, ans = -1, t;
        for (t = 0 ; ; t++) {
            for (int i = n - 1 ; ~i ; i--) {
                data[i].pos += data[i].dir;
                if (data[i].pos == l + 1 || data[i].pos == -1)
                    cnt++, ans = data[i].idx;
            }
            if (cnt == n) break;
            sort(data.begin(), data.end());
            for (int i = 0 ; i < n - 1 ; i++) {
                if (data[i].pos == data[i + 1].pos) {
                    data[i].dir *= -1;
                    data[i + 1].dir *= -1;
                }
            }
        }
        cout << t << ' ' << ans << '\n';
    }
    
}
