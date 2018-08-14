#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
typedef long long LL;
struct DisjointSet{
    int n;
    vector<int> pa;
    DisjointSet(int _n){
        n = _n;
        pa.resize(n + 1, -1);
    }
    int find(int p){
        return pa[p] < 0 ? p : pa[p] = find(pa[p]);
    }
    bool Union(int u, int v){
        int x = find(u), y = find(v);
        if (x != y){
            if (pa[x] < pa[y]) swap(x, y);
            pa[y] += pa[x], pa[x] = y;
        }
        return x != y;
    }
    void Print(){
        for (int i = 0 ; i < n ; i++)
            cout << pa[i] << (i == n-1 ? '\n' : ' ');
    }
};
struct Graph { int n;
    struct Edge {
        int u, v; LL w;
        Edge() {}
        Edge(int _u, int _v, LL _w) {
            u = _u, v = _v, w = _w;
        }
        bool operator < (const Edge &rhs) const {
            return w > rhs.w;
        }
    };
    vector<Edge> edge;
    DisjointSet *djs;
    Graph(int _n) : n(_n) {
        djs = new DisjointSet(n);
    }
    ~Graph() {
        delete djs;
    }
    void addEdge(int u, int v, LL w) {
        edge.push_back(Edge(u, v, w));
    }
    LL MST() {
        LL ret = 0; int cnt = 0;
        sort(edge.begin(), edge.end());
        for (auto e : edge) {
            if (djs->Union(e.u, e.v)) {
                ret += e.w;
                cnt++;
            }
            if (cnt == n - 1) break;
        }
        return ret;
    }
};
int main() {
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        Graph *sol = new Graph(n);
        for (int i = 0 ; i < m ; i++) {
            int u, v; LL w;
            cin >> u >> v >> w;
            u--, v--;
            sol->addEdge(u, v, w);
        }
        cout << sol->MST() << '\n';
        delete sol;
    }
}
