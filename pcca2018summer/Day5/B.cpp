#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const int lgN = __lg(MAXN) + 5;
struct SegmentTree {
    struct Node {
        int L, R; 
        Node *l, *r;
        // data
        int aMax, lMax, rMax;
        Node (int _L = 0,int _R = 0) : L(_L), R(_R) {
            l = r = NULL;
            aMax = lMax = rMax = 0;
        }
    }*rt, buf[lgN << 2], *ptr;
    int *arr; int n;
    SegmentTree(int *_arr, int _n) {
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
            u->aMax = u->lMax = u->rMax = 1;
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
        // pull function
        u->lMax = u->rMax = u->aMax = 0;
        if (arr[l->R - 1] == arr[r->L]) {
            u->lMax = (l->R - l->L == l->lMax) * r->lMax + l->lMax;
            u->rMax = (r->R - r->L == r->rMax) * l->rMax + r->rMax;
            u->aMax = max( { l->rMax + r->lMax, u->lMax, u->rMax } );
        } else {
            u->lMax = l->lMax;
            u->rMax = r->rMax;
            u->aMax = max(l->lMax, r->rMax);
        }
        return u;
    }
    Node* query(int qL, int qR) {
        ptr = buf;
        return query(qL, qR, rt);
    }
    Node* query(int qL, int qR, Node *u) {
        if (u->R <= qL || qR <= u->L) return (Node*)NULL;
        if (qL <= u->L && u->R <= qR) return u;
        return pull(ptr++, query(qL, qR, u->l), query(qL, qR, u->r));
    }
};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; while (cin >> n && n) {
        cin >> q;
        int arr[MAXN]; for (int i = 0 ; i < n ; i++) cin >> arr[i];
        SegmentTree *sol = new SegmentTree(arr, n);
        while (q--) {
            int l, r; cin >> l >> r; l--;
            cout << sol->query(l, r)->aMax << '\n';
        }
        delete sol;
    }
}
