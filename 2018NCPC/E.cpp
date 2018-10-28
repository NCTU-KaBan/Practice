#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second

int n, m, d;
int mine = 0, oppo = 0;
map<pair<int, int>, double> dp;

int power(int x) {
	int ret = 1;
	for (int i = 0; i < x; i ++)
		ret *= 10;
	return ret;
}

double solve(pair<int, int> state, int d) {
	if (d == 0) {
		if (state.S) return 0.0;
		else return 1.0;
	}
	if (state.S == 0 && state.F == 0) return 1.0;
	if (dp.count(state)) return dp[state];
	int cnt = 0;
	double pos = 0;
	for (int i = 1; i < 7; i ++) {
		int next = state.F;
		if (next / power(i) % 10) {
			cnt += next / power(i) % 10;
			next -= power(i);
			next += power(i - 1);
			next -= next % 10;
			pos += (double)(state.F / power(i) % 10) * solve(make_pair(next, state.S), d - 1);
		}
	}
	for (int i = 1; i < 7; i ++) {
		int next = state.S;
		if (next / power(i) % 10) {
			cnt += next / power(i) % 10;
			next -= power(i);
			next += power(i - 1);
			next -= next % 10;
			pos += (double)(state.S / power(i) % 10) * solve(make_pair(state.F, next), d - 1);
		}
	}
	return dp[state] = pos / cnt;
}

int main() {
	cin >> n >> m >> d;

	for (int i = 0; i < n; i ++) {
		int tmp; cin >> tmp;
		mine += power(tmp);
	}

	for (int i = 0; i < m; i ++) {
		int tmp; cin >> tmp;
		oppo += power(tmp);
	}

	cout << fixed << setprecision(8) << solve(make_pair(mine, oppo), d) << '\n';
}
