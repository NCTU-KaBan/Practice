#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<cmath>
#include<set>
#include<algorithm>
#include<vector>
#include<functional>
#define F first
#define S second
using namespace std;
typedef pair<int, int> pii; 
const int MAXN = 2e5 + 5;
int b[MAXN], c[MAXN];
inline bool in(int &ret)
{
    char ch;
    bool sgn = false;//正数
    ret = 0;
    if ((ch = getchar()) == EOF)return false;//EOF
    while (ch != '-' && (ch<'0' || ch>'9')) ch = getchar();
    if (ch == '-') sgn = true;//负数
    else ret = ch - '0';
    while (ch = getchar(), ch >= '0'&&ch <= '9') ret = ret * 10 + ch - '0';
    if (sgn) ret = -ret;
    return true;//当前输入结束
}
inline void out(int n)
{
    if (n < 0) {
        putchar('-'); n = -n;
    }
    if (n > 9) out(n / 10);
    putchar(n % 10 + '0');
}
struct MO {
    struct Q {
        int l, r, b, id;
        Q(int _l, int _r, int _id, int _b) {
            l = _l, r = _r, id = _id, b = _b;
        }
        bool operator < (const Q &q) const {
            return b == q.b ? r < q.r : l < q.l;
        }
    };
    vector<Q> q; vector<int> data;
    int qn, sqn;
    int ans;  // F: cnt, S: num
    MO(vector<int> &_data, vector<pii> &_q) : data(_data) {
        qn = _q.size(), sqn = (int)(sqrt(qn) + 1e-6);
        for (int i = 0 ; i < _q.size() ; i++) {
            Q input(_q[i].F, _q[i].S, i, _q.size() / sqn);
            q.push_back(input);
        }
        ans = 0;
    }
    void pull(int num, int op) {
        if (op ==  1) {
            int &cnt = b[num];
            c[cnt] -= cnt * num;
            cnt++;
            c[cnt] += cnt * num;
            ans = max(cnt, ans);
        }
        if (op == -1) {
            int &cnt = b[num];
            c[cnt] -= cnt * num;
            if (c[cnt] == 0 && ans == cnt) ans--;
            cnt--;
            c[cnt] += cnt * num;
        }
    }
    vector<int> solve() {
        vector<int> ret(qn);
        sort(q.begin(), q.end());
        int l = 0, r = 0;
        for (int i = 0 ; i < q.size() ; i++) {
            Q qu = q[i];
        //for (auto qu : q) {
            
            while (r < qu.r) pull(data[r++],  1);
            while (l > qu.l) pull(data[--l],  1);
            while (r > qu.r) pull(data[--r], -1);
            while (l < qu.l) pull(data[l++], -1);
            ret[qu.id] = ans;
        }
        return ret;
    }
};
int main() {
    int n, m; while (in(n) && n) {
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
	    in(m);
        vector<int> data;
        for (int i = 0 ; i < n ; i++) {
            int input; in(input); 
            input += MAXN / 2;
            data.push_back(input);
        }
        vector<pii> q;
        while (m--) {
            int l, r; in(l); in(r);
            q.push_back(make_pair(l, r));
        }
        MO *sol = new MO(data, q);
        vector<int> ans = sol->solve();
        for (int i = 0 ; i < ans.size() ; i++) {
            out(ans[i]);
            puts("");
        }
        delete sol;
    }
}
