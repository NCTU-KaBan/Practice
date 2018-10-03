#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PNN pair<Node*, Node*>
struct Treap {
    struct Node {
        Node *l, *r;
        int sz;
        pair<int, int> v;
        Node (pair<int, int> _v) : v(_v) {
            l = r = NULL;
            sz = 1;
        }
    }*rt;
    Treap() { rt = NULL; }
    ~Treap() { clear(rt); }
    void clear(Node *u) {
        if (!u) return ;
        clear(u->l); clear(u->r);
        delete u;
    }
    inline int size(Node *u) {
        return u ? u->sz : 0;
    }
    inline Node*& pull(Node *&u) {
        u->sz = 1 + size(u->l) + size(u->r);
        return u;
    }
    PNN split(Node *T, int x) {
        if (!T) return MP((Node*)NULL, (Node*)NULL);
        if (size(T->l) < x) {
            PNN tmp = split(T->r, x - size(T->l) - 1);
            T->r = tmp.F;
            return MP(pull(T), tmp.S);
        } else {
            PNN tmp = split(T->l, x);
            T->l = tmp.S;
            return MP(tmp.F, pull(T));
        }
    }
    Node* merge(Node *T1, Node *T2) {
        if (!T1 || !T2) return T1 ? T1 : T2;
        if (rand() % (size(T1) + size(T2)) < size(T1)) {
            T1->r = merge(T1->r, T2);
            return pull(T1);
        } else {
            T2->l = merge(T1, T2->l);
            return pull(T2);
        }
    }
    
    int rank(pair<int, int> v, Node *u) {
        if (!u) return 0;
        return v <= u->v ? rank(v, u->l) : size(u->l) + rank(v, u->r) + 1;
    }
    void insert(pair<int, int> v) {
        int k = rank(v, rt);
        PNN tmp = split(rt, k);
        rt = merge(merge(tmp.F, new Node(v)), tmp.S);
    }
    void erase(pair<int, int> v) {
        int k = rank(v, rt);
        PNN tmp_1 = split(rt, k + 1);
        PNN tmp_2 = split(tmp_1.F, k);
        rt = merge(tmp_2.F, tmp_1.S);
        delete tmp_2.S;
    }
};
const int MAXN = 1e5 + 5;
int main() {
    int n, m; while (cin >> n >> m) {
        Treap *sol = new Treap();
        pair<int, int> data[MAXN];
        for (int i = 0 ; i < m ; i++) {
            int num, pen; cin >> num >> pen;
            if (num == 1) {
                data[1].F--; data[1].S += pen;
            } else {
                if (data[num].F != 0)
                    sol->erase(data[num]);
                data[num].F--;
                data[num].S += pen;
                sol->insert(data[num]);
            }
            cout << sol->rank(data[1], sol->rt) + 1 << '\n';
        }
        delete sol;
    }
}
