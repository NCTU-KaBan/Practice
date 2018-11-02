#include <bits/stdc++.h>
using namespace std;
int dp[100];
int main() {
    for (int n = 1 ; n < 50 ; n++) {
        int cnt = 0;
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < n ; j++)
                if (i * j % n != 0)
                    cnt++;
        }
        dp[n] = cnt;
    }
    for (int i = 1 ; i < 50 ; i++) {
        int sum = 0;
        for (int j = 1 ; j <= i ; j++) {
            if (i % j == 0) 
                sum += dp[j];
        }
        cout << i << ": " << sum - (i - 1) * (i - 1) << '\n';
    }
}
