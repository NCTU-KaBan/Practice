#include <bits/stdc++.h>
using namespace std;
vector<int> Prime;
vector<bool> isPrime;
const int MAXN = 1299811 + 5;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    isPrime = vector<bool>(MAXN, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2 ; i < MAXN ; i++) {
        if (isPrime[i]) {
            Prime.push_back(i);
            for (int j = i + i ; j < MAXN ; j += i)
                isPrime[j] = false;
        }
    }
    int t; cin >> t; while (t--) {
        int b, e;
        cin >> b >> e;
        for (int i = b - 1 ; i < e ; i++)
            cout << Prime[i] << (i == e - 1 ? '\n' : ' ');
    }
}
