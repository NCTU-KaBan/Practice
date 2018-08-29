#include <bits/stdc++.h>
using namespace std;
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
int main() {
    srand(time(NULL));
    int t = 1;
    int n = 40000, m = 100000;
    while (t--) {
        cout << n << ' ' << m << '\n';
        for (int i = 0 ; i < n ; i++)
            cout << rand() % 100 << ' ';
        cout << '\n';
	    DisjointSet *sol = new DisjointSet(n);	
        for (int i = 0 ; i < n - 1 ; i++) {
            int l = rand() % n, r = rand() % n;
            if (sol->Union(l, r)) 
                cout << l + 1 << ' ' << r + 1 << '\n';
            else i--;
        }
        for (int i = 0 ; i < m ; i++) {
            int l = rand() % n, r = rand() % n;
            cout << l + 1 << ' ' << r + 1 << '\n';
        }
        delete sol;
    }
}
