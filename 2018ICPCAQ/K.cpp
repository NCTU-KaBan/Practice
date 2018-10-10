#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    string s;
    cin >> s;

    if (s[0] == 'D') {
        
        cin >> s;

        for (int i = 0; i < s.size(); i += 2) {
            for (int j = 0; j < (int)(s[i+1] - '0'); j ++)
                cout << s[i];
        }
        cout << '\n';

    } else {

        cin >> s;

        int sum = 1;
        for (int i = 1; i < s.size(); i ++) {
            if (s[i] == s[i - 1]) {
                sum ++;
            } else {
                cout << s[i - 1] << sum;
                sum = 1;
            }
        }
        cout << s[s.size() - 1] << sum << '\n';
    }
}
