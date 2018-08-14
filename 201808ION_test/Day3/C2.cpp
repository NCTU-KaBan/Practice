#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1e4 + 5;
const int lgN = __lg(MAXN) + 5;
typedef long long LL;
struct SegmentTree { int cnt;
    struct Node {
        int L, R; 
        Node *l, *r;
        // data
        LL maxV, secondMaxV;
        // tag
        LL add;
        vector<int> maxPos, secondMaxPos;
        Node (int _L = 0,int _R = 0) : L(_L), R(_R) {
            l = r = NULL;
            add = 0;
            maxPos.clear();
            secondMaxPos.clear();
        }
    }*rt, buf[lgN << 2], *ptr;
    LL *arr; int n;
    SegmentTree(LL *_arr, int _n) {
        arr = _arr, n = _n;
        rt = build(0, n);
    }
    ~SegmentTree() { remove(rt); }
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
            u->maxV =  arr[L];
            u->maxPos.push_back(L);
            u->secondMaxV = -1;
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
        /*
           -------------
           M S       S M
        */
        if (r->maxV > l->maxV) {
            u->maxV = r->maxV;
            u->maxPos = r->maxPos;
            if (l->maxV > r->secondMaxV) {
                u->secondMaxV = l->maxV;
                u->secondMaxPos = l->maxPos;
            } else if (l->maxV < r->secondMaxV) {
                u->secondMaxV = r->secondMaxV;
                u->secondMaxPos = r->secondMaxPos;
            } else {
                u->secondMaxPos.clear();
                for (auto pos : l->maxPos) u->secondMaxPos.push_back(pos);
                for (auto pos : r->secondMaxPos) u->secondMaxPos.push_back(pos);
            }
        } else if (r->maxV < l->maxV) {
            u->maxV = l->maxV;
            u->maxPos = l->maxPos;
            if (l->secondMaxV > r->maxV) {
                u->secondMaxV = l->secondMaxV;
                u->secondMaxPos = l->secondMaxPos;
            } else if (l->secondMaxV < r->maxV) {
                u->secondMaxV = r->maxV;
                u->secondMaxPos = r->maxPos;
            } else {
                u->secondMaxPos.clear();
                for (auto pos : l->secondMaxPos) u->secondMaxPos.push_back(pos);
                for (auto pos : r->maxPos) u->secondMaxPos.push_back(pos);
            }
        } else {
            u->maxV = r->maxV;
            u->maxPos.clear();
            for (auto pos : l->maxPos) u->maxPos.push_back(pos);
            for (auto pos : r->maxPos) u->maxPos.push_back(pos);
            u->secondMaxV = u->maxV;
            u->secondMaxPos = u->maxPos;
        }
        return u;
    }
    void push(Node *u) {
        if (!u) return ;
        // push function
        if (u->add) {
            u->maxV += u->add;
            if (u->secondMaxV != -1) u->secondMaxV += u->add;
            if (u->l) u->l->add += u->add;
            if (u->r) u->r->add += u->add;
            u->add = 0;
        }
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
    void modify(int mL, int mR, LL d) {
        return modify(mL, mR, d, rt);
    }
    void modify(int mL, int mR, LL d, Node *u) {
        if (u->R <= mL || mR <= u->L) return ;
        if (mL <= u->L && u->R <= mR) {
            // modify function
            u->add += d;
            return ;
        }
        push(u);
        modify(mL, mR, d, u->l);
        modify(mL, mR, d, u->r);
        pull(u);
    }
    void Print() {
        cnt = 0;
        Print(rt);
    }
    void Print(Node *u) {
        if (!u) return ;
        push(u);
        Print(u->l);
        if (u->R - u->L == 1) { 
            cout << u->maxV << (cnt == n - 1 ? '\n' : ' ');
            cnt++;
        }
        Print(u->r);
    }
};
int main() {
    int t; cin >> t; while (t--) {
        int n, q; cin >> n >> q;
        LL arr[MAXN];
        for (int i = 0 ; i < n ; i++)
            cin >> arr[i];
        SegmentTree *sol = new SegmentTree(arr, n);
        while (q--) {
            int l, r; LL d;
            cin >> l >> r >> d;
            l--;
            auto target = sol->query(l, r);
            int maxPos = target->maxPos.front();
            int secondMaxPos = target->secondMaxPos.back();
            int qL = min(maxPos, secondMaxPos);
            int qR = max(maxPos, secondMaxPos);
            //cout << qL << ' ' << qR << ' ' << d << '\n';
            sol->modify(qL + 1, qR, d);
        }
        sol->Print();
        delete sol;
    }
}

