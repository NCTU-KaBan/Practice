#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
typedef pair<int, int> pii;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    map<int, int> same;
    int card[MAXN][5][5];
    for (int i = 0 ; i < N ; i++) {
        for (int j = 0 ; j < 5 ; j++) {
            for (int k = 0 ; k < 5 ; k++) {
                int input; cin >> input;
                same[input]++;
                card[i][j][k] = input;
            }
        }
    }
    map<int, int>::iterator it;
    vector<int> S;
    for(it = same.begin(); it != same.end(); it++){
        if(it->second >= 2) S.push_back(it->first);
    }
    map<pii, int> tie;
    for(int si = 0; si < S.size(); si++){
        int s = S[si];
        int row1[5], row2[5];
        int i, l;
        for (i = 0 ; i < N; i++) {
            bool s_in_1 = 0, s_in_2 = 0;
            for(int j = 0; j < 5; j++){
                for(int k = 0; k < 5; k++){
                    row1[k] = card[i][j][k];
                    if(card[i][j][k] == s) s_in_1 = 1;
                }
                if(s_in_1) break;
            }
            for(l = i+1; l < N; l++){
                for(int m = 0; m < 5; m++){
                    for(int n = 0; n < 5; n++){
                        row2[n] = card[l][m][n];
                        if(card[l][m][n] == s) s_in_2 = 1;
                    }
                    if(s_in_2) break;
                }
            }
            if(s_in_1 && s_in_2){
                set<int> seq;
                for(int p = 0; p < 5; p++){
                    seq.insert(row1[p]);
                    seq.insert(row2[p]);
                }
                seq.erase(s);
                int cnt = 0;
                bool if_tie = 1;
                for(int q = l+1; q < N; q++){
                    for(int j = 0; j < 5; j++){
                        for(int k = 0; k < 5; k++){
                            if(seq.count(card[q][j][k])) cnt++;
                        }
                    }
                    if(cnt == 5){
                        if_tie = 0;
                        break;
                    } 
                }
                if(if_tie) tie[pii(i, l)]++;
            }
        }
    }
    if(tie.size()) cout << tie.begin()->first.first + 1 << " " << tie.begin()->first.second + 1 << '\n';
    else cout << "no ties\n";
    return 0;
}
