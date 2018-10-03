#include <bits/stdc++.h>
using namespace std;
struct P {
    string name;
    double F, S;
};
bool cmp_S(const P &p1, const P &p2) {
    return p1.S < p2.S;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; while (cin >> n) {
        vector<P> data(n);
        for (auto &p : data) {
            cin >> p.name >> p.F >> p.S;
        }
        sort(data.begin(), data.end(), cmp_S);
        double sum = 0, minV = 100; int first = -1;
        for (int i = 0 ; i < 4 ; i++) sum += data[i].S;
        for (int i = 0 ; i < n ; i++) {
            if (i < 4) {
                if (minV > sum - data[i].S + data[i].F) {
                    minV = sum - data[i].S + data[i].F;
                    first = i;
                }
            } else {
                if (minV > sum - data[3].S + data[i].F) {
                    minV = sum - data[3].S + data[i].F;
                    first = i;
                }
            }
        }
        cout << minV << '\n';
        cout << data[first].name << '\n';
        for (int i = 0 ; i < 4 ; i++) {
            if (first >= 4 && i == 3) break;
            if (i == first) continue;
            cout << data[i].name << '\n';
        }
    }
}
