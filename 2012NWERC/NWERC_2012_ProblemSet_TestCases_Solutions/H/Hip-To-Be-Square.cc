
/////////////////////////
// Hip-To-Be-Square.cc //
/////////////////////////

// @EXPECTED_RESULTS@: CORRECT

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <cassert>
#include <algorithm>
#include <cmath>

#define ENABLE_SHORTCUT

using namespace std;

typedef vector<unsigned> uvector;

uvector sieve(const unsigned & max_prime)
{
    uvector primes;

    vector<bool> sieve(max_prime + 1, false);

    for (unsigned d = 2; d <= max_prime; ++d)
    {
        if (!sieve[d])
        {
            primes.push_back(d);
            for (unsigned dd = d + d; dd <= max_prime; dd += d)
            {
                sieve[dd] = true;
            }
        }
    }
    return primes;
}

struct Number
{
    Number (const double & value, const uvector & factorization) :
        value(value), factorization(factorization)
    {
    }

    bool operator < (const Number & rhs) const
    {
        return (value < rhs.value);
    }

    bool operator > (const Number & rhs) const
    {
        return (value > rhs.value);
    }

    Number & operator *= (const Number & rhs)
    {
        value *= rhs.value;

        assert(factorization.size() == rhs.factorization.size());

        for (unsigned pi = 0; pi < factorization.size(); ++pi)
        {
            factorization[pi] += rhs.factorization[pi];
        }

        return *this;
    }

    Number operator * (const Number & rhs) const
    {
        Number result(*this);
        result *= rhs;
        return result;
    }

    double value;
    uvector factorization;
};

struct Candidate
{
    Candidate(const Number & number, const uvector & extensions) :
        number(number), extensions(extensions)
    {
    }

    bool operator < (const Candidate & rhs) const
    {
        if (number > rhs.number) return true; // larger number implies lower priority
        if (number < rhs.number) return false; // larger number implies lower priority

        if (extensions > rhs.extensions) return true;
        if (extensions < rhs.extensions) return false;

        return false;
    }

    Number number;
    uvector extensions; // indices of NUMBERS that could be added
};

void solve(unsigned & a, unsigned & b)
{
    assert((1 < a) && (a < b) && (b <= 5000));

    #if ENABLE_SHORTCUT
    {
        unsigned candidate = ceil(sqrt(a));
        unsigned candidate_squared = candidate * candidate;
        if (a <= candidate_squared && candidate_squared <= b)
        {
            cout << candidate << endl;
            return;
        }
    }
    #endif

    uvector PRIMES = sieve(b);

    vector<Number> NUMBERS;

    for (unsigned number = a; number <= b; ++number)
    {
        unsigned factorize_me = number;

        uvector factorization(PRIMES.size(), 0);

        for (unsigned pi = 0; pi < PRIMES.size(); ++pi)
        {
            while (factorize_me % PRIMES[pi] == 0)
            {
                factorize_me /= PRIMES[pi];
                ++factorization[pi];
            }
        }
        assert(factorize_me == 1);

        NUMBERS.push_back(Number(number, factorization));
    }

    // Pruning stage

    for (;;)
    {
        unsigned PRIMES_size_before_sweep  = PRIMES.size();
        unsigned NUMBERS_size_before_sweep = NUMBERS.size();

        for (unsigned pi = 0; pi < PRIMES.size(); ++pi)
        {
            // Count the candidates that have an odd exponent for this prime

            unsigned sum_of_prime_exponents = 0;
            uvector  numbers_with_odd_exponent;

            for (unsigned ni = 0; ni < NUMBERS.size(); ++ni)
            {
                sum_of_prime_exponents += NUMBERS[ni].factorization[pi];

                if (NUMBERS[ni].factorization[pi] % 2)
                {
                    numbers_with_odd_exponent.push_back(ni);
                }
            }

            if (sum_of_prime_exponents == 0)
            {
                // No NUMBER uses this PRIME as a factor. We can safely delete the number from the PRIMES
                // list and all the NUMBERS factorizations.

                PRIMES.erase(PRIMES.begin() + pi);

                for (unsigned ni = 0; ni < NUMBERS.size(); ++ni)
                {
                    NUMBERS[ni].factorization.erase(NUMBERS[ni].factorization.begin() + pi);
                }
            }
            else if (numbers_with_odd_exponent.size() == 1)
            {
                // There is a single NUMBER that has this PRIME as an odd-exponent factor. This implies
                // that that particular NUMBER cannot be a part of a square product, so it is safe
                // to exclude it from further consideration.

                NUMBERS.erase(NUMBERS.begin() + numbers_with_odd_exponent[0]);
            }
            else if (numbers_with_odd_exponent.size() == 2)
            {
                // There are precisely two NUMBERs that have this PRIME as an odd-exponent factor, This implies
                // that these numbers will always occur together in any square. We might as well combine them
                // by multiplying them together.

                // First number becomes the product of the two numbers
                NUMBERS[numbers_with_odd_exponent[0]] *= NUMBERS[numbers_with_odd_exponent[1]];

                // The second number is removed.
                NUMBERS.erase(NUMBERS.begin() + numbers_with_odd_exponent[1]);
            }

        } // loop over primes

        if (PRIMES_size_before_sweep == PRIMES.size() && NUMBERS_size_before_sweep == NUMBERS.size())
        {
            // If there were no changes to the number of PRIMES or NUMBERS, the pruning stage is done.
            break;
        }
    }

    // From now on, NUMBERS is *fixed*, and we can address the numbers contained therein by index.

    // Prepare priority-queue based solver

    priority_queue<Candidate> pq;

    // Add initial candidates to the priority queue

    for (unsigned ni = 0; ni < NUMBERS.size(); ++ni)
    {
        uvector extensions; // Indices for numbers that may be included in the final product.
        for (unsigned ei = ni + 1; ei < NUMBERS.size(); ++ei)
        {
            extensions.push_back(ei);
        }

        pq.push(Candidate(NUMBERS[ni], extensions));
    }

    // Solve

    while (!pq.empty())
    {
        // Find the first prime for which the current candidate number has an odd exponent

        unsigned pi_odd;
        for (pi_odd = 0; pi_odd < pq.top().number.factorization.size(); ++pi_odd)
        {
            if (pq.top().number.factorization[pi_odd] % 2)
            {
                break;
            }
        }

        if (pi_odd == pq.top().number.factorization.size())
        {
            // No prime found for which the candidate number has an odd exponent.
            // This means the candidate is a square, and we're done!
            break;
        }

        // We have at least one odd exponent.

        Candidate c(pq.top());
        pq.pop();

        // We need to generate candidates that are based on the current candidate's number,
        // but having an even exponent in the position where the current candidate has an odd exponent.

        uvector exclude;

        for (unsigned ei = 0; ei < c.extensions.size(); ++ei)
        {
            const Number & extension = NUMBERS[c.extensions[ei]];

            if (extension.factorization[pi_odd] % 2)
            {
                exclude.push_back(c.extensions[ei]);

                uvector new_extensions;
                set_difference(
                    c.extensions.begin(), c.extensions.end(),
                    exclude.begin(), exclude.end(),
                    inserter(new_extensions, new_extensions.begin())
                );

                pq.push(Candidate(c.number * extension, new_extensions));
            }
        }

    } // priority queue loop

    if (pq.empty())
    {
        cout << "none" << endl;
    }
    else
    {
        const Number & square = pq.top().number;

        unsigned long long result = 1;

        for (unsigned pi = 0; pi < square.factorization.size(); ++pi)
        {
            unsigned exponent = square.factorization[pi];
            assert(exponent % 2 == 0);

            while (exponent != 0)
            {
                result *= PRIMES[pi];
                exponent -= 2;
            }
        }

        cout << result << endl;
    }
}

int main()
{
    for (unsigned a, b; cin >> a >> b;)
    {
        solve(a, b);
    }

    return 0;
}
