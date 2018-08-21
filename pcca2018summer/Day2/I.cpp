#include <bits/stdc++.h>
using namespace std;
#define PNN pair<Node*, Node*>
#define MP make_pair
#define F first
#define S second
int n, cnt;
struct Treap{
    struct Node{
        Node *l, *r;
        int sz, v;
        // data
        // tag
        bool rev;
        Node (int _v) : v(_v){
            l = r = NULL;
            sz = 1; 
            rev = false;
        }
    }*rt;
    Treap(){ rt = NULL; }
    ~Treap(){ clear(rt); }
    void clear(Node *u){
        if (!u) return ;
        clear(u->l); clear(u->r);
        delete u;
    }
    inline int size(Node *u){
        return u ? u->sz : 0;
    }
    inline Node*& pull(Node *&u){
        u->sz = 1 + size(push(u->l)) + size(push(u->r));
        // pull function
        return u;
    }
    inline Node*& push(Node *&u){
        if (!u) return u;
        // push function
        if (u->rev) {
            swap(u->l, u->r);
            if (u->l) {
                u->l->rev ^= 1;
            }
            if (u->r) {
                u->r->rev ^= 1;
            }
            u->rev = false;
        }
        return u;
    }
    PNN split(Node *T, int x){
        if (!T) return MP((Node*)NULL, (Node*)NULL);
        if (size(push(T)->l) < x){
            PNN tmp = split(T->r, x - size(T->l) - 1);
            T->r = tmp.F;
            return MP(pull(T), tmp.S);
        }else{
            PNN tmp = split(T->l, x);
            T->l = tmp.S;
            return MP(tmp.F, pull(T));
        }
    }
    Node* merge(Node *T1, Node *T2){
        if (!T1 || !T2) return T1 ? T1 : T2;
        if (rand() % (size(T1) + size(T2)) < size(T1)){
            T1->r = merge(push(T1)->r, T2);
            return pull(T1);
        }else{
            T2->l = merge(T1, push(T2)->l);
            return pull(T2);
        }
    }
    void push_back(int v) {
        rt = merge(rt, new Node(v));
    }
    void Print(Node *u) {
        if (!u) return ;
        push(u);
        Print(u->l);
        cout << u->v;
        cnt++;
        cout << (cnt == n ? '\n' : ' ');
        Print(u->r);
    }
    void cut_and_move(int a, int b, int c) {
        PNN tmp_1 = split(rt, b);
        PNN tmp_2 = split(tmp_1.F, a - 1);
        rt = merge(tmp_2.F, tmp_1.S);
        PNN tmp_3 = split(rt, c);
        rt = merge(merge(tmp_3.F, tmp_2.S), tmp_3.S);
    }
    void reverse(int a, int b) {
        PNN tmp_1 = split(rt, b);
        PNN tmp_2 = split(tmp_1.F, a - 1);
        tmp_2.S->rev ^= 1;
        rt = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
};
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; while (cin >> n >> q) {
        cnt = 0;
        if (n == -1 && q == -1) break;
        Treap *sol = new Treap();
        for (int i = 1 ; i <= n ; i++)
            sol->push_back(i);
        while (q--) {
            string op; cin >> op;
            int a, b, c;
            if (op[0] == 'C') {
                cin >> a >> b >> c;
                sol->cut_and_move(a, b, c);
            } else if (op[0] == 'F') {
                cin >> a >> b;
                sol->reverse(a, b);
            }
        }
        sol->Print(sol->rt);
        delete sol;
    }
}
