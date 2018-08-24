#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
#define PNN pair<Node*, Node*>
#define MP make_pair
#define F first
#define S second
const int MAXN = 2e6 + 5;
struct Treap{
    struct Node{
        Node *l, *r;
        int sz; char v;
        // tag
        Node (char _v = 0) : v(_v){
            l = r = NULL;
            sz = 1; 
        }
    }*rt, _mem[MAXN], *ptr;
    Treap(){ rt = NULL; ptr = _mem; }
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
    void insert(char c, int p) {
        PNN tmp = split(rt, p);
        rt = merge(merge(tmp.F, new (ptr++) Node(c)), tmp.S);
    }
    char query(int p) {
        PNN tmp_1 = split(rt, p);
        PNN tmp_2 = split(tmp_1.F, p - 1);
        char c = tmp_2.S->v;
        rt = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
        return c;
    }
    void push_back(char c) {
        rt = merge(rt, new (ptr++) Node(c));
    }
};
int main(){ ios_base::sync_with_stdio(false); cin.tie(0);
    string s; while (cin >> s) {
        Treap *sol = new Treap();
        for (int i = 0 ; i < s.size() ; i++)
            sol->push_back(s[i]);
        int q; cin >> q; while (q--) {
            string op; cin >> op;
            if (op[0] == 'Q') {
                int p; cin >> p;
                cout << sol->query(p) << '\n';
            }
            if (op[0] == 'I') {
                char c; int p;
                cin >> c >> p;
                sol->insert(c, p - 1);
            }
        }
        delete sol;
    }
}
