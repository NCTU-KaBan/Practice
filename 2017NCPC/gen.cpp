#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(NULL));
    int n = 500, m = 500; cout << n << ' ' << m << '\n';
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j < m ; j++) {
                cout << -i-1 << (j == m - 1 ? '\n' : ' ');
        }
    cout << 500 << ' ' << 500 << '\n';
}
