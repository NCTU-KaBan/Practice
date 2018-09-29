// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>

#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;

struct Variable
{
    Variable() : val(-1) {}
    VI imply[2];
    int val;
};

typedef vector<Variable> VV;

bool assign(VV &vars, int x, int v) {
    if( vars[x].val >= 0 ) {
        return (vars[x].val == v);
    }
    vars[x].val = v;
    for( int k = 0; k < int(vars[x].imply[v].size()); ++k ) {
        int y = vars[x].imply[v][k];
        int yv = (y<0)?0:1;
        if( !assign(vars, abs(y)-1, yv) ) {
            vars[x].val = -1;
            return false;
        }
    }
    return true;
}

void solve() {
    int n, m; if( scanf("%d%d", &n, &m) != 2 ) { exit(0); }
    VV vars(n);
    for( int i = 0; i < m; ++i ) {
        int a, b; if( scanf("%d%d", &a, &b) != 2 ) { fprintf(stderr, "No more clause!\n"); exit(1); }
        if( abs(a) > n || abs(b) > n ) { 
            fprintf(stderr, "clause %d %d is unacceptable (n=%d)\n", a, b, n);
            exit(1);
        }
        if( a < 0 ) { vars[-a-1].imply[1].push_back(b); }
        if( a > 0 ) { vars[a-1].imply[0].push_back(b); }
        if( b < 0 ) { vars[-b-1].imply[1].push_back(a); }
        if( b > 0 ) { vars[b-1].imply[0].push_back(a); }
    }
    for( int x = 0; x < n; ++x ) {
        VV oldvars(vars);
        if( assign(vars, x, 1) ) {
            continue;
        }
        if( x == 0 ) { puts("no"); return; }
        vars = oldvars;
        if( !assign(vars, x, 0) ) {
            puts("no");
            return;
        }
    }
    puts("yes");
}

int main() {
    while( true ) { solve(); }
    return 0;
}
