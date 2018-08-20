#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
#define MP make_pair
struct Point {
    int x, y;
    Point (int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &p) const {
        return MP(x, y) < MP(p.x, p.y);
        // return atan2(y, x) < atan2(p.y, p.x);
    }
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const int &d) const {
        return Point(d * x, d * y);
    }
    int operator * (const Point &p) const {
        return x * p.x + y * p.y;
    }
    int operator % (const Point &p) const {
        return x * p.y - y * p.x;
    }
    friend int abs2(const Point &p) {
        return p * p;
    }
    friend double abs(const Point &p) {
        return sqrt(abs2(p));
    }
};
vector<Point> ConvexHull(vector<Point> &p) {    // begin and end is same
    sort(p.begin(), p.end());
    vector<Point> ans; int m = 0;
    for (int i = 0 ; i < p.size() ; i++) {
        while (m >= 2 && (p[i] - ans[m - 2]) % (ans[m - 1] - ans[m - 2]) < 0) ans.pop_back(), m--;
        ans.push_back(p[i]), m++;
    }
    for (int i = p.size() - 2 ; i >= 0 ; i--) {
        while (m >= 2 && (p[i] - ans[m - 2]) % (ans[m - 1] - ans[m - 2]) < 0) ans.pop_back(), m--;
        ans.push_back(p[i]), m++;
    }
    return ans;
}
int area(Point a, Point b, Point c) {
    int ret2 = abs(a.x * b.y + b.x * c.y + c.x * a.y
                - (a.y * b.x + b.y * c.x + c.y * a.x));
    return ret2;
}
int main() {
    int n; while (cin >> n && n != -1) {
        vector<Point> data;
        for (int i = 0 ; i < n ; i++) {
            int x, y; cin >> x >> y;
            Point input;
            input.x = x;
            input.y = y;
            data.push_back(input);
        }
        vector<Point> res = ConvexHull(data);
        res.pop_back();
        n = res.size();
        int a = 0, b = 1, c = 2, maxV = -1;
        for (a = 0 ; a < n ; a++) {
            while (area(res[a], res[b], res[(c + 1) % n]) > area(res[a], res[b], res[c]))
                c = (c + 1) % n;
            maxV = max(maxV, area(res[a], res[b], res[c]));
            while (area(res[a], res[(b + 1) % n], res[c]) > area(res[a], res[b], res[c]))
                b = (b + 1) % n;
            maxV = max(maxV, area(res[a], res[b], res[c]));
        }
        cout << fixed << setprecision(2) << maxV / 2.0 << '\n';
    }
}
