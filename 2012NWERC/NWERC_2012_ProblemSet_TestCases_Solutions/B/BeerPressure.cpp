
// @EXPECTED_RESULTS@: CORRECT

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>

#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve() {
    int n, k; if( scanf("%d%d", &n, &k) != 2 ) exit(0);
    ll start = 0ll;
    vector<ll> pow100; pow100.push_back(1ll);
    for( int i = 0; i < n; ++i ) {
        ll x; scanf("%lld", &x);
        start *= 100ll;
        start += x;
        pow100.push_back(100ll**pow100.rbegin());
    }
    map<ll,double> chance; chance[start] = 100.0;
    vector<double> result(n, 0.0);
    queue<ll> q; q.push(start);
    while( q.size() > 0 ) {
        vector<int> state(n);
        ll cur = q.front(); q.pop();
        double p = chance[cur];
        ll tmp = cur;
        int total = 0;
        for( int i = n-1; i >= 0; --i ) {
            state[i] = int(tmp%100ll);
            tmp /= 100ll;
            total += state[i];
        }
        if( total == k ) {
            vector<int> winners;
            winners.push_back(0);
            for( int i = 1; i < n; ++i ) {
                if( state[i] == state[winners[0]] ) {
                    winners.push_back(i);
                }
                if( state[i] > state[winners[0]] ) {
                    winners.clear();
                    winners.push_back(i);
                }
            }
            for( int i = 0; i < winners.size(); ++i ) {
                result[winners[i]] += p/(double)winners.size();
            }
        } else {
            for( int i = 0; i < n; ++i ) {
                ll next = cur + pow100[n-1-i];
                double c = (double)state[i]/(double)total;
                map<ll,double>::iterator it = chance.find(next);
                if( it != chance.end() ) {
                    it->second += c*p;
                } else {
                    chance[next] = c*p;
                    q.push(next);
                }
            }
        }
    }
    for( int i = 0; i < n; ++i ) {
        printf("pub %d: %.2f %%\n", i+1, result[i]);
    }
}

int main() {
    while( true ) solve();
}
