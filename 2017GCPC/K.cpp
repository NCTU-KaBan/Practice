#include <bits/stdc++.h>
using namespace std;
struct P {
    string name;
    long long c;
    P(string _n, long long _c) : name(_n), c(_c) {}
    bool operator < (const P &p) const {
        return c > p.c;
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    vector<P> data;
    int n, k; long long d; cin >> n >> d >> k;
    for (int i = 0 ; i < n ; i++) {
        string name; long long c;
        cin >> name >> c;
        data.emplace_back(name, c);
    }
    sort(data.begin(), data.end());
    vector<string> ans;
    long long sum = 0;
    for (int i = 0 ; i < k ; i++) {
        sum += data[i].c;
        ans.push_back(data[i].name);
        if (sum >= d) break;
    }
    if (sum >= d) {
        cout << ans.size() << '\n';
        for (auto s : ans) {
            cout << s << ", YOU ARE FIRED!\n";
        }
    } else {
        cout << "impossible\n";
    }
}
