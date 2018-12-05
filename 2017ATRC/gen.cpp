#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(NULL));
    int n = 10000, t = 100000;
    cout << n << ' ' << t << '\n';
    for (int i = 0 ; i < n ; i++)
        cout << rand() % 10000 + 1 << '\n';
}
