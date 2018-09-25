#include <bits/stdc++.h>
using namespace std;
struct P {
    long long x, y; 
};
long long A(P b, P c) {
    return b.x * c.y - b.y * c.x;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<P> data;
    for (int i = 0 ; i < n ; i++) {
        long long x, y; cin >> x >> y;
        data.push_back({x, y});
    }
    data.push_back(data.front());
    long long area = 0, b = 0;
    for (int i = 0 ; i < n ; i++) {
        area += A(data[i], data[i + 1]);
        b += __gcd(abs(data[i].x - data[i + 1].x), abs(data[i].y - data[i + 1].y));
    }
    area = abs(area);
    cout << (area - b + 2) / 2 << '\n';
}
