#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define PNN pair<Node*, Node*> 
#define MP make_pair
#define F first
#define S second
const int MAXN = 2e5 + 5;
struct Treap {
    struct Node {
        Node *l, *r;
        LL v, add, minV; int pri, sz;
        bool rev;
        Node (LL _v = 0) {
            v = _v;
            pri = rand();
            sz = 1;
            l = r = NULL;
            add = rev = 0;
            minV = v;
        }
    }*rt, _mem[MAXN], *ptr;
    Treap() { ptr = _mem; }
    inline int size(Node *u) { return u ? u->sz : 0; }
    inline void pull(Node *u) {
        u->sz = 1 + size(u->l) + size( u->r);
        u->minV = u->v;
        if (u->l) {
            push(u->l);
            u->minV = min(u->minV, u->l->minV);
        }
        if (u->r) {
            push(u->r);
            u->minV = min(u->minV, u->r->minV);
        }
    }
    inline void push(Node *u) {
        if (u->add) {
            u->v += u->add;
            u->minV += u->add;
            if (u->l) u->l->add += u->add;
            if (u->r) u->r->add += u->add;
            u->add = 0;
        }
        if (u->rev) {
            swap(u->l, u->r);
            if (u->l) u->l->rev ^= 1;
            if (u->r) u->r->rev ^= 1;
            u->rev = false;
        }
    }
#define PNN pair<Node*, Node*>
#define MP make_pair
#define F first
#define S second
    PNN split(Node *T, int x) {
        if (!T) return MP((Node*)NULL, (Node*)NULL);
        push(T);
        if (size(T->l) < x) {
            PNN tmp = split(T->r, x - size(T->l) - 1);
            T->r = tmp.F;
            pull(T);
            return MP(T, tmp.S);
        } else {
            PNN tmp = split(T->l, x);
            T->l = tmp.S;
            pull(T);
            return MP(tmp.F, T);
        }
    }
    Node* merge(Node *T1, Node *T2) {
        if (!T1 || !T2) return T1 ? T1 : T2;
        if (T1->pri < T2->pri) {
            push(T2);
            T2->l = merge(T1, T2->l);
            pull(T2);
            return T2;
        } else {
            push(T1);
            T1->r = merge(T1->r, T2);
            pull(T1);
            return T1;
        }
    }
    void insert(LL v, int k = -1) {
        if (!~k) k = size(rt) + 1;
        PNN tmp = split(rt, k);
        rt = merge(merge(tmp.F, new (ptr++) Node(v)), tmp.S);
    }
    void addValue(int x, int y, LL v) {
        PNN tmp_1 = split(rt, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        tmp_2.S->add += v;
        rt = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
    void erase(int k) {
        PNN tmp_1 = split(rt, k);
        PNN tmp_2 = split(tmp_1.F, k - 1);
        rt = merge(tmp_2.F, tmp_1.S);
    }
    int minValue(int x, int y) {
        PNN tmp_1 = split(rt, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        LL res = tmp_2.S->minV;
        rt = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
        return res;
    }
    void reverse(int x, int y) {
        PNN tmp_1 = split(rt, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        tmp_2.S->rev ^= 1;
        rt = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
    void revolve(int x, int y, int t) {
        PNN tmp_1 = split(rt, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        int len = y - x + 1;
        t %= len;
        PNN tmp_3 = split(tmp_2.S, len - t);
        tmp_2.S = merge(tmp_3.S, tmp_3.F);
        rt = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    Treap *sol = new Treap();
    int n; cin >> n; for (int i = 0 ; i < n ; i++) {
        LL tmp; cin >> tmp;
        sol->insert(tmp);
    }
    int q; cin >> q;
    while (q--) {
        char op[10]; cin >> op;
        int x, y; LL k;
        switch(op[0]) {
            case 'A':
                cin >> x >> y >> k;
                sol->addValue(x, y, k);
                break;
            case 'R':
                if (op[3] == 'O') {
                    cin >> x >> y >> k;
                    sol->revolve(x, y, k);
                }
                if (op[3] == 'E') {
                    cin >> x >> y;
                    sol->reverse(x, y);
                }
                break;
            case 'I':
                cin >> x >> k;
                sol->insert(k, x);
                break;
            case 'D':
                cin >> x;
                sol->erase(x);
                break;
            case 'M':
                int x, y; cin >> x >> y;
                cout << sol->minValue(x, y) << '\n';
                break;
        }
    }
    delete sol;
}
