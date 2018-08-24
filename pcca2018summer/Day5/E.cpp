#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 5;
const int lgN = __lg(MAXN) + 5;
struct SegmentTree {
    struct Node {
        int L, R; 
        Node *l, *r;
        // data
        int v, maxV;
        // tag
        Node (int _L = 0,int _R = 0) : L(_L), R(_R) {
            l = r = NULL;
            v = maxV = 0;
        }
    }*rt, buf[lgN << 2], *ptr;
    LL *arr; int n;
    SegmentTree(LL *_arr, int _n) {
        arr = _arr, n = _n;
        rt = build(0, n);
    }

    ~SegmentTree() {
        remove(rt);
    }
    void remove(Node *u) {
        if (!u) return ;
        remove(u->r);
        remove(u->l);
        delete u;
    }
    Node* build(int L, int R) {
        Node *u = new Node(L, R);
        if (R - L == 1) {
            // basic data
            u->v = u->maxV = arr[L];
            return u;
        }
        int M = (R + L) >> 1;
        u->l = build(L, M);
        u->r = build(M, R);
        return pull(u);
    }
    Node* pull(Node *u) {
        return pull(u, u->l, u->r);
    }
    Node* pull(Node *u, Node *l, Node *r) {
        if (!l || !r) return l ? l : r;
        push(l); push(r);
        // pull function;
        u->maxV = max(l->maxV, r->maxV);
        return u;
    }
    void push(Node *u) {
        if (!u) return ;
        // push function
    }
    Node* query(int qL, int qR) {
        ptr = buf;
        return query(qL, qR, rt);
    }
    Node* query(int qL, int qR, Node *u) {
        if (u->R <= qL || qR <= u->L) return (Node*)NULL;
        if (qL <= u->L && u->R <= qR) return u;
        push(u);
        return pull(ptr++, query(qL, qR, u->l), query(qL, qR, u->r));
    }
    void modify(int mL, int mR, LL v) {
        return modify(mL, mR, v, rt);
    }
    void modify(int mL, int mR, LL v, Node *u) {
        if (u->R <= mL || mR <= u->L) return ;
        if (mL <= u->L && u->R <= mR) {
            // modify function
            u->v = u->maxV = v;
            return ;
        }
        push(u);
        modify(mL, mR, v, u->l);
        modify(mL, mR, v, u->r);
        pull(u);
    }
};
int main() { //ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        LL data[MAXN];
        for (int i = 0 ; i < n ; i++) cin >> data[i];
        SegmentTree *sol = new SegmentTree(data, n);
        string op; LL l, r;;
        while (m--) {
            cin >> op >> l >> r; l--;
            if (op[0] == 'Q') {
                cout << sol->query(l, r)->maxV << '\n';
            }
            if (op[0] == 'U') {
                sol->modify(l, l + 1, r);
            }
        }
        delete sol;
    }
}
