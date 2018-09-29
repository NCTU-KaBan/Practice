#include <bits/stdc++.h>
using namespace std;
const int BASE = 1e9 + 0.5;
const int WIDTH = log10(BASE) + 0.5;
template <typename T>
inline string to_string(const T &x) {
    stringstream ss;
    return ss << x, ss.str();
}
typedef long long LL;
struct bigN : vector<LL> {
    bigN(string s) {
        if (s.empty()) return ;
        for (int i = s.size() - 1 ; i >= 0 ; i -= WIDTH) {
            LL t = 0;
            for (int j = max(0, i - WIDTH + 1) ; j <= i ; j++)
                t = t * 10 + s[j] - '0';
            push_back(t);
        }
        trim();
    }
    bigN() {}
    template <typename T>
    bigN(const T &x) : bigN(to_string(x)) {}
    friend istream &operator >> (istream &in, bigN &b) {
        string s;
        return in >> s, b = s, in;
    }
    friend ostream& operator << (ostream &out, const bigN &b) {
        out << (b.empty() ? 0 : b.back());
        for (int i = b.size() - 2 ; i >= 0 ; i --) {
            out << setw(WIDTH) << setfill('0') << b[i];
        }
        return out;
    }
    inline void trim() {
        while (size() && !back()) pop_back();
    }
    bigN operator + (const bigN &b) const {
        bigN res = *this;
        if (b.size() > size()) res.resize(b.size());
        for (int i = 0 ; i < b.size() ; i++) res[i] += b[i];
        return res.carry(), res.trim(), res;
    }
    inline void carry() {
        for (int i = 0 ; i < size() ; i++) {
            if (at(i) >= 0 && at(i) < BASE) continue;
            if (i + 1 == size()) push_back(0);
            int r = at(i) % BASE;
            if (r < 0) r += BASE;
            at(i + 1) += (at(i) - r) / BASE;
            at(i) = r;
        }
    }
};
bigN dp[2][10005][2];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    dp[0][3][0] = 2;
    dp[0][3][1] = 1;
    dp[1][3][0] = 1;
    dp[1][3][1] = 1;
    for (int i = 4 ; i < 10005 ; i++) {
        dp[0][i][0] = dp[0][i - 1][0] + dp[0][i - 1][1];
        dp[1][i][0] = dp[1][i - 1][0] + dp[1][i - 1][1];
        dp[0][i][1] = dp[0][i - 1][0];
        dp[1][i][1] = dp[1][i - 1][0];
    }
    int n; while (cin >> n) {
        cout << dp[0][n][0] + dp[0][n][1] + dp[1][n][0] << '\n';
    }
}
