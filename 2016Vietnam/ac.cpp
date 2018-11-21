#include <bits/stdc++.h>
using namespace std;
#define ms(a,x) memset(a, x, sizeof(a))
#define mod 1000000007
#define sz(a) ((ll)(a).size())

#define Rep(i,n) for(int i = 0; i < (n); ++i)
#define Repd(i,n) for(int i = (n)-1; i >= 0; --i)
#define For(i,a,b) for(int i = (a); i <= (b); ++i)
#define Ford(i,a,b) for(int i = (a); i >= (b); --i)

typedef long long ll;

#define maxn 21

int num;
int test;
int n, a[maxn];
ll f[maxn][maxn][10][2];

ll go(int id, int so, int du, int behon){
//	cout << id << " " << so << " " << du << " " << behon << endl;
	if(id < 0){
		if(du == 0) return so;
		else return 0;
	}
	ll &ret = f[id][so][du][behon];
	if(ret != -1) return ret;
	ret = 0;
	int l = 0, r = 9;
	if(!behon) r = a[id];
	For(i, l, r){
		int dnew = (du * 10 + i) % 8;
		int sonew = so;
		if(i == 8 || i == 6) sonew++;
		ret += go(id - 1, sonew, dnew, behon | (i < a[id]));
	}
	return ret;
}

ll dem(ll X){
	ll res = 0;
	while(X){
		ll d = X % 10;
		res += (d == 6 || d == 8);
		X /= 10;
	}
	return res;
}

void sol(){
	ms(f, -1); ms(a, 0);
	ll X, temp;
	cin >> X;
	temp = X - 1;
	n = 0;
	while(temp){
		a[n++] = temp % 10;
		temp /= 10;
	}

	cout << go(19, 0, 0, 0) + dem(X) << "\n";
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> test;
	Rep(itest, test){
		sol();
	}

    return 0;
}
