
// @EXPECTED_RESULTS@: CORRECT

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{

  ios::sync_with_stdio(true);

  for (unsigned int x; cin >> x;) {

    unsigned int n;
    cin >> n;

    if (n == 0) {
      cout << "danger" << endl;
    }
    else if (n == 1) {
      unsigned int tmp;
      cin >> tmp;
      cout << "danger" << endl;
    }
    else {
      vector<int> v;
      v.reserve(n);
    
      for (; v.size() < n;) {
	unsigned int l;
	cin >> l;
	v.push_back(l);
      }
    
      sort (v.begin(), v.end());
      
      int left = 0;
      int right = v.size() - 1;
      bool found = false;
      x = x * 10000000;
      
      while (left < right) {
	if (v[left] + v[right] == x) {
	  cout << "yes " << v[left] << " " << v[right] << endl;
	  found = true;
	  left++;
	  break;
	}
	else if (v[left] + v[right] < x) {
	  left++;
	}
	else
	  right--;
      }

      if (!found)
	cout << "danger" << endl;
    }
  }
  return 0;
}
