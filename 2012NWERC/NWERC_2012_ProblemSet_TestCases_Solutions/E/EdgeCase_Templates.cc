
// @EXPECTED_RESULTS@: COMPILER-ERROR

// To compile this, you will need to ...
//
// (1) raise the recursive template instantiation limit of your compiler (g++: ftemplate-depth=11000)
// (2) have a lot of memory (g++ : ~ 22 Gb)
// (3) have a lot of patience (g++: ~ 8 hours)

#include <iostream>
#include <iomanip>

typedef unsigned long long DigitType;

const unsigned BASE_DIGITS = 18;
const DigitType BASE = 1000000000000000000ULL;

using namespace std;

// Define a DigitList as a "little endian" list of digits.

template <DigitType digit>
struct Digit
{
    static const DigitType value = digit;
};

struct Nil
{
};

template <typename Head, typename Tail>
struct DigitList
{
    typedef Head head; // least significant digit
    typedef Tail tail;
};

// Printing a DigitList

template <typename DigitList>
struct DigitListPrinter;

template <DigitType digit>
struct DigitListPrinter<DigitList<Digit<digit>, Nil> >
{
    static void run()
    {
        cout << digit;
    }
};

template <DigitType digit, typename Tail>
struct DigitListPrinter<DigitList<Digit<digit>, Tail> >
{
    static void run()
    {
        DigitListPrinter<Tail>::run();

        cout << setfill('0') << setw(BASE_DIGITS) << digit;
    }
};

// Adding two DigitList types to yield another DigitList

template <typename Lhs, typename Rhs, DigitType carry>
struct Adder;

template <typename H1, typename T1, typename H2, typename T2, DigitType carry>
struct Adder<DigitList<H1, T1>, DigitList<H2, T2>, carry>
{
    typedef DigitList<
            Digit<(H1::value + H2::value + carry) % BASE>,
            typename Adder<T1, T2, (H1::value + H2::value + carry) / BASE>::value
        > value;
};

template <>
struct Adder<Nil, Nil, 0>
{
    typedef Nil value;
};

template <DigitType carry>
struct Adder<Nil, Nil, carry>
{
    typedef DigitList<Digit<carry>, Nil> value;
};

template <DigitType digit, DigitType carry>
struct Adder<DigitList<Digit<digit>, Nil>, Nil, carry>
{
    typedef typename Adder<DigitList<Digit<digit>, Nil>, DigitList<Digit<carry>, Nil>, 0>::value value;
};

// Define the Lucas sequence

template <unsigned n>
struct Lucas
{
    typedef typename Adder<typename Lucas<n - 1>::value, typename Lucas<n - 2>::value, 0>::value value;
};

template <> struct Lucas<0> { typedef DigitList<Digit<2>, Nil> value; };
template <> struct Lucas<1> { typedef DigitList<Digit<1>, Nil> value; };

// Print the Lucase sequence (link run-time to compile-time)

template <unsigned max_n>
void PrintLucas(unsigned n)
{
    if (n == max_n)
    {
        DigitListPrinter<typename Lucas<max_n>::value>::run();
    }
    else
    {
        PrintLucas<max_n - 1>(n);
    }
}

template <>
void PrintLucas<0>(unsigned)
{
    DigitListPrinter<Lucas<0>::value>::run();
}

int main()
{
    const unsigned max_n = 10000;

    for (unsigned n; cin >> n; )
    {
        PrintLucas<max_n>(n);
        cout << endl;
    }

    return 0;
}
