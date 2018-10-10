#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    set<int> card[MAXN];
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < 5 ; j++) {
            for (int k = 0 ; k < 5 ; k++) {
                int input; cin >> input;
                card[i].insert(input);
            }
        }
    }
    for (int i = 0 ; i < n ; i++) {
        for (int j = i + 1 ; j < n ; j++) {
            for (auto inte : card[i]) {
                if (card[j].count(inte)) {
                    cout << i + 1 << ' ' << j + 1 << '\n';
                    return 0;
                }
            }
        }
    }
    cout << "no ties\n";
}
