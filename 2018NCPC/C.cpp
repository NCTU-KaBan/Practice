#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> day;
    for (int i = 0 ; i < n ; i++) {
        int num; cin >> num;
        day.push_back(num);
    }
    int cur = 0, w = 0;
    for (int i = 1 ; i < 365 ; i++) {
        if (day[cur] >= i) continue;
        int sum = 0, j;

        

        for (j = cur ; j < day.size() && day[j] < i + 1; j++)
            sum += i + 1 - day[j];
        if (sum >= 20) {
            w++, cur = j;
        }
    }
    if (cur != day.size()) w++;
    cout << w << '\n';
}
