#include <bits/stdc++.h>
using namespace std;
void H(int n, char A, char B, char C) {
    if (n == 0) return ;
    H(n - 1, A, C, B);
    cout << "put " << n << " from " << A << " to " << C << '\n';
    H(n - 1, B, A, C);
}
int main() {
    int n; cin >> n;
    H(n, 'A', 'B', 'C');
}
