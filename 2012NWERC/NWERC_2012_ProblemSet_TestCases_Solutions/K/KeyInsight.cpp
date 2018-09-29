// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <set>
using namespace std;

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII> VPII;
typedef set<VI> SVI;
typedef long long ll;

#define MAX 1000

char text1[MAX], text2[MAX];

ll count(int len, int parts) {
    VVI ij(len), ji(len);
    ll num = 1ll;
    for( int i = 0; i < len; ++i ) {
        for( int j = 0; j < len; ++j ) {
            bool ok = true;
            for( int k = 0; k < parts; ++k ) {
                if( text1[i+k*len] != text2[j+k*len] ) {
                    ok = false;
                    break;
                }
            }
            if( !ok ) { continue; }
            ij[i].push_back(j);
            ji[j].push_back(i);
        }
    }
    SVI svi;
    for( int i = 0; i < len; ++i ) {
        if( ij[i].size() == 0 ) { return 0ll; }
        for( int k = 0; k < int(ij[i].size()); ++k ) {
            int j = ij[i][k];
            if( ji[j].size() != ij[i].size() ) { return 0ll; }
            if( k == 0 ) {
                svi.insert(ji[j]);
            } else {
                if( svi.count(ji[j]) == 0 ) { return 0ll; }
            }
        }
    }
    SVI svj;
    for( int j = 0; j < len; ++j ) {
        if( ji[j].size() == 0 ) { return 0ll; }
        for( int k = 0; k < int(ji[j].size()); ++k ) {
            int i = ji[j][k];
            if( ji[j].size() != ij[i].size() ) { return 0ll; }
            if( k == 0 ) {
                svj.insert(ij[i]);
            } else {
                if( svj.count(ij[i]) == 0 ) { return 0ll; }
            }
        }
    }
    for( SVI::iterator it = svi.begin(); it != svi.end(); ++it ) {
        ll c = it->size();
        while( c > 1ll ) { num *= c--; }
    }
    return num;
}

void solve() {
    int k; if( scanf("%d%s%s", &k, text1, text2) != 3 ) { exit(0); }
    int len = strlen(text1);
    ll ans = count(k,len/k);
    printf("%lld\n", ans);
}

int main() {
    while( true ) solve();
    return 0;
}
