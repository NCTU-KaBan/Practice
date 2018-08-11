#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; cin >> t; while (t--) {
        stack<char> stk;
        string input; cin >> input;
        bool legal = true;
        int cnt[3]; memset(cnt, 0, sizeof(cnt));    // 0: (, 1: [, 2: {
        for (int i = 0 ; i < input.size() && legal ; i++) {
            if (input[i] == ')') {
                if (stk.empty() || stk.top() != '(') legal = false;
                else stk.pop();
                cnt[0]--;
            } else if (input[i] == ']') {
                if (stk.empty() || stk.top() != '[') legal = false;
                else stk.pop();
                cnt[1]--;
            } else if (input[i] == '}') {
                if (stk.empty() || stk.top() != '{') legal = false;
                else stk.pop();
                cnt[2]--;
            } else {
                if (input[i] == '(') cnt[0]++;
                else if (input[i] == '[') {
                    if (cnt[0] != 0) legal = false;
                    cnt[1]++;
                } else if (input[i] == '{') {
                    if (cnt[0] != 0 || cnt[1] != 0) legal = false;
                    cnt[2]++;
                }
                stk.push(input[i]);
            }
        }
        if (stk.size()) legal = false;
        if (legal) cout << "Yes\n";
        else cout << "No\n";
    }
}
