#include <bits/stdc++.h>
using namespace std;
char intToChar(int inte) {
    if (inte == 1)      return 'N';
    if (inte == 5)      return 'T';
    if (inte == 10)     return 'H';
    if (inte == 50)     return 'U';
    if (inte == 100)    return 'S';
    if (inte == 500)    return 'E';
    if (inte == 1000)   return 'A';
    if (inte == 5000)   return 'C';
    if (inte == 10000)  return 'O';
    if (inte == 50000)  return 'W';
}
int charToInt(char c) {
    if (c == 'N') return 1;
    if (c == 'T') return 5;
    if (c == 'H') return 10;
    if (c == 'U') return 50;
    if (c == 'S') return 100;
    if (c == 'E') return 500;
    if (c == 'A') return 1000;
    if (c == 'C') return 5000;
    if (c == 'O') return 10000;
    if (c == 'W') return 50000;
}
string transToStr(int inte) {
    stringstream ss; ss << inte;
    string s; ss >> s;
    string res = "";
    for (int i = 0 ; i < s.size() ; i++) {
        int base = 1;
        for (int j = 0 ; j < s.size() - i - 1 ; j++)
            base *= 10;
        int target = s[i] - '0';
        if (target == 0) continue;
        else if (target < 4) {
            for (int j = 0 ; j < target ; j++)
                res += intToChar(base);
        } else if (target == 4) {
            res += intToChar(base);
            res += intToChar(5 * base);
        } else if (target < 9) {
            res += intToChar(5 * base);
            for (int j = 0 ; j < target - 5 ; j++)
                res += intToChar(base);
        } else if (target == 9) {
            res += intToChar(base);
            res += intToChar(10 * base);
        }
    }
    return res;
}
int transToInt(string input) {
    vector<int> data; data.push_back(charToInt(input[0]));
    for (int i = 1 ; i < input.size() ; i++) {
        data.push_back(charToInt(input[i]));
        if (data[i - 1] < data[i]) data[i - 1] *= -1;
    }
    int res = 0;
    for (int i = 0 ; i < data.size() ; i++)
        res += data[i];
    return res;
}
int main() {
    string st; cin >> st;
    int t = transToInt(st); for (int i = 0 ; i < t ; i++) {
        string sa, sb; cin >> sa >> sb;
        cout << "Case " << transToStr(i + 1) << ": " << transToStr(transToInt(sa) + transToInt(sb)) << '\n';
    }
    
}
