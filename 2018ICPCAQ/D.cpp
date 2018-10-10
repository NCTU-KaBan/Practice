#include <bits/stdc++.h>
using namespace std;
const int MAXN = 25;
int trans(int x, int m) {
    while (x < 0) x += m;
    return x % m;
}


int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    int n, W; cin >> n >> W;
    int O[MAXN], I[MAXN], S[MAXN];
    for (int i = n - 1 ; i >= 0 ; i--)
        cin >> O[i] >> I[i] >> S[i];
    int x = -1, y; cin >> y;
    string s; cin >> s;
    bool dead = false;
    for (int i = 0 ; i < (int)s.size() ; i++) {		
        if (s[i] == 'U') {
            x++;
        } else if (s[i] == 'D') {
            x--;
        } else if (s[i] == 'L') {
            y--;
        } else if (s[i] == 'R') {
            y++;
        }
        if (x == n) break;
        if (I[x] == 1) {
            dead = true;
            break;
        }
        /*
        if (i != s.size() - 1) {
        cout << "X " << x << ' ' << "Y " << y << '\n';
            if (x % 2 == n % 2) {
                
            cout << "trans " << trans(y - i * S[x] - O[x], I[x]) << '\n';
            cout << "S " << S[x] << '\n';
                if (trans(y - i * S[x] - O[x], I[x]) <= S[x])
                    dead = true;
            } else {
            cout << "trans " << trans(y + i * S[x] - O[x], I[x]) << '\n';
            cout << "S " << S[x] << '\n';
                if (trans(y + i * S[x] - O[x], I[x]) <= S[x])
                    dead = true;
            }
        cout << "dead " << dead << '\n';
        }
        */
        //cout << "t " << i << '\n';
        if (x >= 0) {
         //cout << "X " << x << ' ' << "Y " << y << '\n';
         //cout << "S O I\n";
         //cout << S[x] << ' ' << O[x] << ' ' << I[x] << '\n';
            if (S[x] == 0) {
            } else {
                if (x % 2 == n % 2) {
                    //cout << "trans " << trans(y - (i + 1) * S[x] - O[x], I[x]) << '\n';
                    //cout << "S " << S[x] << '\n';
                    int check = trans(y - i * S[x] - O[x], I[x] * S[x]);
                    if (check < S[x] && check > 0)
                        dead = true;
                } else {
                     //cout << "trans " << trans(y + (i + 1) * S[x] - O[x], I[x]) << '\n';
                     //cout << "S " << S[x] << '\n';
                    int check = trans(y + i * S[x] - O[x], I[x] * S[x]);
                    if (check < S[x] && check > 0)
                        dead = true;
                }
              //cout << "dead " << dead << '\n';
            }
        }
        if (dead) break;
    }
    // cout << x << ' ' << n << '\n';
    if (x < n) dead = true;
    if (dead) cout<< "squish\n";
    else cout << "safe\n";
}
