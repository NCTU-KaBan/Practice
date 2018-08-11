#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
LL ADD(LL a, LL b) { return (a + 2 * b) % MOD; }
LL SUB(LL a, LL b) { return (2 * a + b) % MOD; }
LL MUL(LL a, LL b) { return a * (a + b) % MOD; }
LL DIV(LL a, LL b) { return (a + b) * b % MOD; }
LL strToLL(string input) {
    LL res = 0;
    for (int i = 0 ; i < input.size() ; i++)
        res = res * 10 + input[i] - '0';
    return res;
}
int priority(char c) {
    if (c == '+' || c == '-') return 0;
    if (c == '*' || c == '/') return 1;
}
void calculate(stack<char> &toSuf, stack<LL> &cal) {
    char op = toSuf.top(); toSuf.pop();
     LL S = cal.top(); cal.pop();
     LL F = cal.top(); cal.pop();
     if (op == '+')      cal.push(ADD(F, S));
     else if (op == '-') cal.push(SUB(F, S));
     else if (op == '*') cal.push(MUL(F, S));
     else if (op == '/') cal.push(DIV(F, S)); 
}
int main() {
    int t; cin >> t; while (t--) {
        stack<char> toSuf;
        stack<LL> cal;
        int n; cin >> n;
        for (int i = 0 ; i < n ; i++) {
            string input; cin >> input;
            if (isdigit(input[0])) 
                cal.push(strToLL(input));
            else {
                while (toSuf.size() && priority(toSuf.top()) >= priority(input[0]))
                    calculate(toSuf, cal);
                toSuf.push(input[0]);
            }
        }
        while (toSuf.size()) calculate(toSuf, cal);
        cout << cal.top() << '\n';

    }
}
