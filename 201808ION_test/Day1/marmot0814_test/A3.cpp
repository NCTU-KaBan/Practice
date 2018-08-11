#include <bits/stdc++.h>
using namespace std;
int main() {
    string input; while (getline(cin, input, ';')) {
        string s; stringstream ss; ss << input;
        int ans = 0; bool haveWord = false;
        while (ss >> s) {
            haveWord = true;
            int delta;
            if (s[0] == 'b') delta = 0;
            else if (s[0] == 'f') delta = 1;
            else if (s[0] == 'u') delta = 2;
            else if (s[0] == 'p') delta = 3;
            else if (s[0] == 't') delta = 4;
            ans = ans * 5 + delta;
        }
        if (haveWord) cout << ans << '\n';
        else cout << "Manatee space\n";
        
    }
}
