#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        double sum = 0;
        for (int i = 0 ; i < n ; i++) {
            double input; cin >> input;
            sum += input;
        }
        sum = max(0.0, sum);
        printf("%.2f\n", (int)( sum * 87 + .5 ) / 100.0);
    }
}
