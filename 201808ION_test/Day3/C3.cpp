#include <bits/stdc++.h>
using namespace std;

int main() {

	int T;
	cin >> T;

	while (T --) {
		
		int N, M, S;
		cin >> N >> M >> S; //friends, props, food

		int sum[1005] = {0}, Max = -1; sum[0] = 1; //+1
		for (int i = 0; i < N; i ++) {
			
			int eat, weight;
			cin >> eat >> weight;

			for (int j = 1000; j >= eat; j --) {
				if (sum[j - eat]) {
					// cout << sum[j - eat] << endl;
					if (sum[j - eat] + weight > sum[j])
						sum[j] = sum[j - eat] + weight;
					if (sum[j] > Max && j <= S) Max = sum[j];
				}
			}			
		}
		
		Max --;

		int current, value, Ans = -1;
		int propsum[1001] = {0}; propsum[0] = 1;

		for (int i = 0; i < M; i ++) {
			cin >> current >> value;
			for (int j = 1000; j >= current; j --) {
				if (propsum[j - current]) {
					if (propsum[j - current] + value > propsum[j])
						propsum[j] = propsum[j - current] + value;
					if (propsum[j] > Ans && j <= Max) Ans = propsum[j];
				}
			}
		}
		
		cout << --Ans << endl;

	}

}
