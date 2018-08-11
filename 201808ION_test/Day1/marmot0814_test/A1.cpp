#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        double sum = 0;
        for (int i = 0 ; i < n ; i++) {
            double input; cin >> input;
            bool neg = false;
            if (input < 0) neg = true, input *= -1;
            input = (int)(input * 87 + 0.5) / 100.0;
            if (neg) input *= -1;
            sum += input;
        }
        cout << fixed << setprecision(2) << max(0.0, sum) << '\n';
    }
}
