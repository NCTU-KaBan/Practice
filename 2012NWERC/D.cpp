#include <bits/stdc++.h>
using namespace std;
void OR(bool *target, bool *arr) {
   for (int i = 0 ; i < 7 ; i++)
       target[i] |= arr[i];
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    /*
    int alpha[10][10] = {
        {0, 7, 1},
        {1},
        {2},
        {1, 3, 7},
        {1, 4},
        {5},
        {5, 6},
        {1, 7},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 
        {1, 3, 4, 7, 9},
    };
    */
    bool a[10][10]; memset(a, false, sizeof(a));
    a[0][0] = true; a[0][1] = true; a[0][7] = true;
    a[1][1] = true;
    a[2][2] = true;
    a[3][1] = true; a[3][3] = true; a[3][7] = true;
    a[4][1] = true; a[4][4] = true;
    a[5][5] = true;
    a[6][5] = true; a[6][6] = true;
    a[7][1] = true; a[7][7] = true;
    a[8][0] = true; a[8][1] = true; a[8][2] = true; a[8][3] = true; a[8][4] = true; 
    a[8][5] = true; a[8][6] = true; a[8][7] = true; a[8][8] = true; a[8][9] = true;
    a[9][1] = true; a[9][3] = true; a[9][4] = true; a[9][7] = true; a[9][9] = true;
    bool digit[10][7] = {
        {1, 1, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1},
        {0, 1, 1, 0, 0, 1, 0},
        {1, 1, 1, 1 ,1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1}
    };
    //big, small
    int n; while (cin >> n) {
        vector<pair<int, int> > data;
        bool display[4][7];
        memset(display, false, sizeof(display));
        for (int i = 0 ; i < n ; i++) {
            int h, m; char c; cin >> h >> c >> m;
            data.emplace_back(h, m);
            OR(display[0], digit[h / 10]);
            OR(display[1], digit[h % 10]);
            OR(display[2], digit[m / 10]);
            OR(display[3], digit[m % 10]);
        }
        bool _find = false, first = true;
        for (int _h = 0 ; _h < 24 ; _h++) {
            for (int _m = 0 ; _m < 60 ; _m++) {
                int curh = _h, curm = _m;
                bool legal = true;

                for (int i = 0 ; i < n && legal ; i++) {
                    if (a[curh / 10][data[i].first  / 10] 
                     && a[curh % 10][data[i].first  % 10]
                     && a[curm / 10][data[i].second / 10]
                     && a[curm % 10][data[i].second % 10]) {
                        for (int j = 0 ; j < 7 ; j++) {
                            if ((!digit[data[i].first  / 10][j] && digit[curh / 10][j] && display[0][j])
                             || (!digit[data[i].first  % 10][j] && digit[curh % 10][j] && display[1][j])
                             || (!digit[data[i].second / 10][j] && digit[curm / 10][j] && display[2][j])
                             || (!digit[data[i].second % 10][j] && digit[curm % 10][j] && display[3][j])) {
                                legal = false;
                                break;
                            }
                        }
                        curm++; curm %= 60;
                        if (curm == 0) curh++;
                        curh %= 24;
                    } else legal = false;
                }
                if (!legal) continue;
                _find = true;
                if (first) first = false;
                else cout << ' ';
                cout << setw(2) << setfill('0') << _h;
                cout << ":";
                cout << setw(2) << setfill('0') << _m;
            }
        }
        if (!_find) cout << "none\n";
        else cout << '\n';
    }
}
