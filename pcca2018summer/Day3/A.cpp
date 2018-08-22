#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define F first
#define S second
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1000 + 5;
const int MAXM = (MAXN * MAXN) / 2;
struct Graph{
    struct Node; struct Edge;
    int V;
    struct Node : vector<Edge*>{
        iterator cur; int d;
        Node(){ clear(); }
    }_memN[MAXN], *node[MAXN];
    struct Edge{
        Node *u, *v; 
        Edge *rev;
        LL c, f;
        Edge(){}
        Edge(Node *u, Node *v, LL c, Edge *rev) : u(u), v(v), c(c), f(0), rev(rev){}
    }_memE[MAXM], *ptrE;
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
        ptrE = _memE;
    }
    void addEdge(int _u, int _v, LL _c){
        *ptrE = Edge(node[_u], node[_v], _c, ptrE + 1);
        node[_u]->PB(ptrE++);
        *ptrE = Edge(node[_v], node[_u], 0, ptrE - 1);
        node[_v]->PB(ptrE++);
    }
    
    Node *s, *t;
    LL maxFlow(int _s, int _t){
        s = node[_s], t = node[_t];
        LL flow = 0;
        while (bfs()) {
            for (int i = 0 ; i < V ; i++)
                node[i]->cur = node[i]->begin();
            flow += dfs(s, INF);
        }
        return flow;
    }
    bool bfs(){
        for (int i = 0 ; i < V ; i++) node[i]->d = -1;
        queue<Node*> q; q.push(s); s->d = 0;
        while (q.size()) {
            Node *u = q.front(); q.pop();
            for (auto e : *u) {
                Node *v = e->v;
                if (!~v->d && e->c > e->f)
                    q.push(v), v->d = u->d + 1;
            }
        }
        return ~t->d;
    }
    LL dfs(Node *u, LL a){
        if (u == t || !a) return a;
        LL flow = 0, f;
        for (; u->cur != u->end() ; u->cur++) {
            auto &e = *u->cur; Node *v = e->v;
            if (u->d + 1 == v->d && (f = dfs(v, min(a, e->c - e->f))) > 0) {
                e->f += f; e->rev->f -= f;
                flow += f; a -= f;
                if (!a) break;
            }
        }
        return flow;
    }
};
int main(){ ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    set<int> time;
    vector<pair<int, int> > ori_time;
    for (int i = 0 ; i < n;  i++) {
        pair<int, int> pii;
        cin >> pii.F >> pii.S;
        ori_time.push_back(pii);
        time.insert(pii.F);
        time.insert(pii.S);
    }
    vector<int> vtime;
    for (auto t : time) 
        vtime.push_back(t);
    vector<pair<int, int> > time_seg;
    for (int i = 1 ; i < vtime.size() ; i++) 
        time_seg.push_back(make_pair(vtime[i - 1], vtime[i]));


    int L = 0, R = 10005;
    while (R - L > 1) {
        int M = (R + L) >> 1;
        Graph *sol = new Graph(n + time_seg.size() + 2);
        for (int i = 0 ; i < n ; i++) 
            sol->addEdge(0, i + 1, M);
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < time_seg.size() ; j++) {
                if (ori_time[i].F <= time_seg[j].F && time_seg[j].S <= ori_time[i].S) 
                    sol->addEdge(i + 1, n + j + 1, INF);
            }
        }
        for (int j = 0 ; j < time_seg.size() ; j++)
            sol->addEdge(n + j + 1, n + time_seg.size() + 1, time_seg[j].S - time_seg[j].F);
        if (sol->maxFlow(0, n + time_seg.size() + 1) == (n * M)) 
            L = M;
        else
            R = M;
        delete sol;
    }
    cout << L * n << '\n';
}
