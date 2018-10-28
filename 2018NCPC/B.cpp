#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    bool legal = true;
    for (int i = 0 ; i < n ; i++) {
        string s;
        cin >> s;
        if (s[0] == 'm') continue;
        stringstream ss; ss << s;
        int inte; ss >> inte;
        if (inte != i + 1) legal = false;
    }
    if (legal) cout << "makes sense\n";
    else cout << "something is fishy\n";
}
