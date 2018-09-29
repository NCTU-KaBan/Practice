
//////////////////////
// Joint-Venture.cc //
//////////////////////

// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    for (unsigned x, n; cin >> x >> n; )
    {
        x *= 10000000; // cm to nm

        vector<unsigned> piece;
        piece.reserve(n);

        for (unsigned sz; piece.size() < n; )
        {
            cin >> sz;
            piece.push_back(sz);
        }

        sort(piece.begin(), piece.end());

        int i = 0;
        int j = n - 1;

        while (i < j)
        {
            if (piece[i] + piece[j] == x)
            {
                break;
            }

            if (piece[i] + piece[j] < x)
            {
                // piece[i] can never be part of a solution
                ++i;
            }
            else // piece[i] + piece[j] > x
            {
                // piece[j] can never be part of a solution
                --j;
            }
        }

        if (i < j)
        {
            cout << "yes " << piece[i] << " " << piece[j] << endl;
        }
        else
        {
            cout << "danger" << endl;
        }

    }

    return 0;
}
