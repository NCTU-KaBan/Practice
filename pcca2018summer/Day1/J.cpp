#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<int, int> pii;
int main() {
    vector<pii> data;
    int n; cin >> n; for (int i = 0 ; i < n ; i++) {
        pii input; cin >> input.F >> input.S;
        data.push_back(input);
    }
    map<pair<int, int>, int> cnt;
    for (int i = 0 ; i < n ; i++) {
        for (int j = i + 1 ; j < n ; j++) {
            pii p; 
            p.F = data[i].F - data[j].F;
            p.S = data[i].S - data[j].S;
            if (p.F == 0) p.S = abs(p.S);
            if (p.F < 0) p.F *= -1, p.S *= -1;
            cnt[p]++; 
        }
    }
    vector<pair<pair<int, int>, int> > res;
    for (auto p : cnt) {
        pair<pair<int, int>, int> input;
        input.F.F = p.F.F;
        input.F.S = p.F.S;
        input.S = p.S;
        if (input.S != 1)
            res.push_back(input);
    }
    int ans = 0;
    for (int i = 0 ; i < res.size() ; i++) {
        ans += res[i].S * (res[i].S - 1) / 2;
    }
    ans /= 2;
    cout << ans << '\n';
}
