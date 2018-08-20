#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
struct Point {
    int x, y;
}p[MAXN];
int n;
double interpolate_x(int y, Point p1, Point p2) {
    if (p1.y == p2.y) return p1.x;
    return p1.x + (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
}
bool point_in_polygon(Point t) {
    bool c = false;
    for (int i = n - 1, j = 0 ; j < n ; i = j++) {
        if ((p[i].y > t.y != p[j].y > t.y) && t.x < interpolate_x(t.y, p[i], p[j]))
                c = !c;
    }
    return c;
}
int main() {
    while (cin >> n) {
        for (int i = 0 ; i < n ; i++) {
            cin >> p[i].x >> p[i].y;
        }
        int q; cin >> q; while (q--) {
            Point target;
            cin >> target.x >> target.y;
            cout << (point_in_polygon(target) ? "Yes\n" : "No\n");
        }
    }
}
