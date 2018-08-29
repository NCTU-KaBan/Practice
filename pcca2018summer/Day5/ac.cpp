#include <bits/stdc++.h>
using namespace std;

#define FIN(x) freopen(#x".txt", "r", stdin)

typedef long long LL;
void debug() { cout << endl; }
template<typename T, typename ...R> void debug (T f, R ...r) { cout << "[" << f << "]"; debug (r...); }

const int MAXN = 40005;
const int MAXM = 100005;
const int DEEP = 30;

int n, m, block;
struct Edge {
    int v, next;
} edge[MAXN << 1];
int head[MAXN], tot, st[MAXN], ed[MAXN], tim, dep[MAXN], fa[MAXN][DEEP];
int seq[MAXN << 1];
int w[MAXN], f[MAXN], fsz;

void init_edge() {
    tim = tot = 0;
    memset(head, -1, sizeof(head));
}
inline void add_edge(int u, int v) {
    edge[tot] = Edge{v, head[u]};
    head[u] = tot ++;
}

void dfs(int u, int pre, int deep) {
    int v;
    dep[u] = deep; fa[u][0] = pre;
    st[u] = ++ tim; seq[tim] = u;
    for(int i = head[u]; ~i; i = edge[i].next) {
        v = edge[i].v;
        if(v == pre || v == u) continue;
        dfs(v, u, deep + 1);
    }
    ed[u] = ++ tim; seq[tim] = u;
}

int lca(int u, int v) {
    while(dep[u] != dep[v]) {
        if(dep[u] < dep[v]) swap(u, v);
        int d = dep[u] - dep[v];
        for(int i = 0; i < DEEP; ++i) {
            if(d >> i & 1) u = fa[u][i];
        }
    }
    if(u == v) return u;
    for(int i = DEEP - 1; i >= 0; --i) {
        if(fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

struct Query {
    int L, R, bid, qid;
    int lca;
    Query() {}
    Query(int _L, int _R, int _lca, int _qid) : L(_L), R(_R), lca(_lca), qid(_qid) {
        bid = L / block;
    }
    bool operator < (const Query& e) {
        if(bid == e.bid) return R < e.R;
        return bid < e.bid;
    }
} qr[MAXM];
int Ans[MAXM];

struct Set {
    int vis[MAXN];
    int sz;
    void clear() { sz = 0; memset(vis, 0, sizeof(vis)); }
    void insert(int x) {
        if(!vis[x]) ++ sz;
        ++ vis[x];
    }
    void erase(int x) {
        -- vis[x];
        if(!vis[x]) -- sz;
    }
    int size() { return sz; }
} path_set;
bool in_path[MAXN];
inline void QModify(int x) {
    int u = seq[x];
    if(in_path[u]) path_set.erase(w[u]);
    else path_set.insert(w[u]);
    in_path[u] ^= 1;
}
int main() {
#ifdef ___LOCAL_WONZY___
    FIN(input);
#endif // ___LOCAL_WONZY___
    int u, v;
    while (~scanf("%d %d", &n, &m)) {
    fsz = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &w[i]);
        f[++ fsz] = w[i];
    }
    sort(f + 1, f + fsz + 1);
    fsz = unique(f + 1, f + fsz + 1) - f - 1;
    for(int i = 1; i <= n; ++i)  w[i] = lower_bound(f + 1, f + fsz + 1, w[i]) - f;
    init_edge();
    for(int i = 2; i <= n; ++i) {
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 1, 0);
    for(int i = 1; i < DEEP; i++) {
        for(int j = 1; j <= n; j++) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    block = sqrt(n * 2);
    int mm = 0;
    for(int i = 1; i <= m; ++i) {
        scanf("%d %d", &u, &v);
        if(u == v) {
            Ans[i] = 1;
            continue;
        }
        if(st[u] > st[v]) swap(u, v);
        int p = lca(u, v);
        if(p == u) {
            qr[++ mm] = Query(st[u], st[v], p, i);
        } else {
            qr[++ mm] = Query(ed[u], st[v], p, i);
        }
    }
    sort(qr + 1, qr + mm + 1);
    int L = 1, R = 0;
    memset(in_path, 0, sizeof(in_path));
    path_set.clear();

    for(int i = 1; i <= mm; ++i) {
        while(L > qr[i].L) QModify(--L);    //ins
        while(R < qr[i].R) QModify(++R);   //ins
        while(L < qr[i].L) QModify(L++);   //del
        while(R > qr[i].R) QModify(R--);   //del
        if(qr[i].lca != seq[qr[i].L] && qr[i].lca != seq[qr[i].R]) QModify(st[qr[i].lca]);  // ins
        Ans[qr[i].qid] = path_set.size();
        if(qr[i].lca != seq[qr[i].L] && qr[i].lca != seq[qr[i].R]) QModify(st[qr[i].lca]);  // del
    }
    for(int i = 1; i <= m; ++i) printf("%d\n", Ans[i]);
#ifdef ___LOCAL_WONZY___
    cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << "ms." << endl;
#endif // ___LOCAL_WONZY___
    }
    return 0;
}
