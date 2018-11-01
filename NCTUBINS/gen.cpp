#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(NULL));
    int t = 100; cout << t << '\n';
    while (t--) {
        int n = 10; cout << n << '\n';
        for (int i = 0 ; i < n ; i++)
            cout << rand() % 1000000000 << ' ';
        cout << '\n';
    }
}
