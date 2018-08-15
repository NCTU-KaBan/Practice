#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;

LL fpow(LL a, int b) { //a**b
	if (b == 0) return 1;
	if (b == 1) return a;
	else if (b % 2) return fpow(a, b - 1) * a;
	else return fpow(a, b / 2) * fpow(a, b / 2);
}

LL F(LL N) {
	return 45 * N * fpow(10, N - 1);
}

LL find(LL X, LL N) {
	return F(N) * (X + 1) + X * (X + 1) / 2 * fpow(10, N);
}

LL solve(LL target) {
	LL sum = 0, ans = 0;
	LL cp_tar = target;
	while (cp_tar) {
		sum += cp_tar % 10;
		cp_tar /= 10;
	}

	int d = 0;
	int current;
	while (target) {
		current = target % 10;
		sum -= current;
		if (d == 0) ans += current * (current + 1) / 2 + sum * (current + 1);
		else {
			ans += find(current - 1, d) + sum * (current * fpow(10, d));
		}

		target /= 10;
		d ++;
	}
	return ans;
}

int main() {
	
	int T;
	cin >> T;

	while (T --) {
		LL start, end;
		cin >> start >> end;

		cout << solve(end) - solve(start - 1) << endl;
	}
}
