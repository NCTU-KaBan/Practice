
/////////////////////
// BeerPressure.cc //
/////////////////////

// @EXPECTED_RESULTS@: CORRECT

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <map>
#include <sstream>
#include <cassert>
#include <algorithm>

using namespace std;

typedef vector<unsigned>     unsigned_vector;
typedef vector<double>       probability_vector;
typedef unsigned long long   MemoKey;
typedef map<MemoKey, double> Memo;

const unsigned MAX_STUDENTS = 50;

MemoKey to_key(const unsigned_vector & v)
{
    MemoKey k = 0;
    for (unsigned_vector::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        k *= (MAX_STUDENTS + 1);
        k += *it;
    }
    return k;
}

template <typename TSeq>
inline unsigned sum(const TSeq & sequence)
{
    return accumulate(sequence.begin(), sequence.end(), 0);
}

double calculate_recursive(const unsigned_vector & alpha, const unsigned_vector & beta, Memo & memo)
{
    unsigned numBins = alpha.size();
    assert(beta.size() == numBins);

    bool equal = true;

    for (unsigned i = 0; i < numBins; ++i)
    {
        if (beta[i] < alpha[i])
        {
            return 0;
        }

        if (beta[i] != alpha[i])
        {
            equal = false;
        }
    }

    if (equal)
    {
        return 1.0;
    }

    const MemoKey key = to_key(beta);

    const Memo::const_iterator found = memo.find(key);

    if (found != memo.end())
    {
        // found -- return previously calculated value
        return found->second;
    }

    // not found -- we must calculate the probability

    double probability = 0.0;

    unsigned_vector beta_updated(beta);

    unsigned sum_beta_minus_one = sum(beta) - 1;

    for (unsigned i = 0; i < numBins; ++i)
    {
        --beta_updated[i];
        probability += calculate_recursive(alpha, beta_updated, memo) * beta_updated[i] / sum_beta_minus_one;
        ++beta_updated[i];
    }

    memo.insert(make_pair(key, probability));

    return probability;
}

void solve_recursive(const unsigned_vector    & alpha,
                           unsigned_vector    & beta,
                     const unsigned             studentsLeft,
                     const unsigned             idx,
                           Memo               & memo,
                           probability_vector & probabilities)
{
    if (idx == beta.size())
    {
        if (studentsLeft == 0)
        {
            const double solutionProbability = calculate_recursive(alpha, beta, memo);

            const unsigned maxVoteCount = *max_element(beta.begin(), beta.end());

            const unsigned countWinners = count(beta.begin(), beta.end(), maxVoteCount);

            const double probabilityPerWinner = solutionProbability / countWinners;

            for (unsigned i = 0; i < beta.size(); ++i)
            {
                if (beta[i] == maxVoteCount)
                {
                    probabilities[i] += probabilityPerWinner;
                }
            }
        }
    }
    else
    {
        if (studentsLeft != 0)
        {
            ++beta[idx];
            solve_recursive(alpha, beta, studentsLeft - 1, idx, memo, probabilities);
            --beta[idx];
        }

        solve_recursive(alpha, beta, studentsLeft, idx + 1, memo, probabilities);
    }
}

int main()
{
    cout << fixed << setprecision(2);

    for (unsigned n, k; cin >> n >> k;)
    {
        assert(1 <= n && n <= 5);
        assert(1 <= k && k <= 50);

        unsigned_vector alpha(n);

        for (unsigned i = 0; i < alpha.size(); ++i)
        {
            cin >> alpha[i];
        }

        assert(k >= sum(alpha));

        probability_vector probabilities(n, 0.0);

        Memo memo;

        unsigned_vector beta(alpha);

        solve_recursive(alpha, beta, k - sum(beta), 0, memo, probabilities);

        for (unsigned i = 0; i < n; ++i)
        {
            cout << "pub " << (i + 1) << ": " << 100.0 * probabilities[i] << " %" << endl;
        }
    }

    return 0;
}
