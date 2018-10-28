#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 128;
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int MAXM = 105;
int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    long long n, m; cin >> n >> m;
    char tmp = getchar();
    char s[MAXLEN];
    vector<int> ansList; int minV = INF;
    char name[MAXM][MAXLEN];
    for (int i = 0 ; i < m ; i++) {
        fgets(s, MAXLEN, stdin);
        strtok(s, "\n");
        char *chp = strtok(s, ",");
        sscanf(chp, "%[^\t\n]s", name[i]);
        chp = strtok(NULL, ",");
        long long p, t, c, r;
        sscanf(chp, "%I64d", &p);
        chp = strtok(NULL, ",");
        sscanf(chp, "%I64d", &c);
        chp = strtok(NULL, ",");
        sscanf(chp, "%I64d", &t);
        chp = strtok(NULL, ",");
        sscanf(chp, "%I64d", &r);
        double period = t + r;
        double ans = 10080.0 / period * t * c;
        if (ans >= n) {
            if (minV == p) {
                ansList.push_back(i);
            } else if (minV > p) {
                ansList.clear();
                minV = p;
                ansList.push_back(i);
            }
        }
    }
    if (ansList.size() == 0) {
        cout << "no such mower\n";
    } else for (int i = 0 ; i < ansList.size() ; i++) {
        cout << name[ansList[i]] << '\n';
    }
}
