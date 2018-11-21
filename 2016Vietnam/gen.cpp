#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(NULL));
    int n = 100000; cout << n << '\n';
    for (int i = 0 ; i < n;  i++) {
        cout << rand() % 10000000 << '\n';
    }
    cout << '\n';
}
