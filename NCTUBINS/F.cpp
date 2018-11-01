#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<int> data(n);
        for (auto &num : data) cin >> num;
        vector<int> L[2], R[2]; // 0 assend, 1, dessend
        L[0].push_back(1); L[1].push_back(1);
        for (int i = 1 ; i < n ; i++) {
            if (data[i] <= data[i - 1]) L[0].push_back(L[0].back() + 1);
            else L[0].push_back(1);
            if (data[i] >= data[i - 1]) L[1].push_back(L[1].back() + 1);
            else L[1].push_back(1);
        }
        R[0].push_back(1); R[1].push_back(1);
        for (int i = n - 2 ; i >= 0 ; i--) {
            if (data[i] <= data[i + 1]) R[0].push_back(R[0].back() + 1);
            else R[0].push_back(1);
            if (data[i] >= data[i + 1]) R[1].push_back(R[1].back() + 1);
            else R[1].push_back(1);
        }
        reverse(R[0].begin(), R[0].end());
        reverse(R[1].begin(), R[1].end());
/*
        cout << "data\nLas\nLde\nRas\nRde\n";
        for (int i = 0 ; i < n ; i++)
            cout << data[i] << ' ';
        cout << '\n';
        for (int k = 0 ; k < 2 ; k++) {
            for (int i = 0 ; i < n ; i++)
                cout << L[k][i] << ' ';
            cout << '\n';
        }

        for (int k = 0 ; k < 2 ; k++) {
            for (int i = 0 ; i < n ; i++)
                cout << R[k][i] << ' ';
            cout << '\n';
        }
*/
        bool legal = false;
        if (L[0][n - 1] == n || L[1][n - 1] == n || R[0][0] == n || R[1][0] == n) {
            cout << "YES\n";
            continue;
        }
        if (L[1][n - 2] == n - 1 || L[0][n - 2] == n - 1 || R[1][1] == n - 1 || R[0][1] == n - 1) {
            cout << "YES\n";
            continue;
        }
        for (int i = 1 ; i < n - 1 && !legal ; i++) {
            if (data[i - 1] <= data[i + 1] && L[1][i - 1] + R[0][i + 1] == n - 1)
                legal = true;
            if (data[i - 1] >= data[i + 1] && L[0][i - 1] + R[1][i + 1] == n - 1)
                legal = true;
        }
        if (legal) cout << "YES\n";
        else cout << "NO\n";
    }
}
