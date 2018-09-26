#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        int sum = 0, minV = 1e7;
        for (int i = 0 ; i < n;  i++) {
            int input; cin >> input;
            sum += input;
            minV = min(minV, input);
        }
        if (n % 2) {
            if (sum % 2) cout << "Yalalov\n";
            else cout << "Shin\n";
        } else {
            if (sum % 2) { 
                cout << "Yalalov\n";
                continue;
            }
            if (minV % 2) cout << "Yalalov\n";
            else cout << "Shin\n";
        }
    }
}
