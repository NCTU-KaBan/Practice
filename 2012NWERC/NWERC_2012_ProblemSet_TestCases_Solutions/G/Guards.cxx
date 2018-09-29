// Programming language: C++11
// @EXPECTED_RESULTS@: CORRECT

#include <set>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

struct Corridor
{
    Corridor(const unsigned & a, const unsigned & b): a(a), b(b) {}
    unsigned a;
    unsigned b;
};

struct Wing
{
    Wing(unsigned nHalls, unsigned linkNode, const vector<Corridor> & icorridors, const vector<Corridor> & xcorridors, const vector<Wing> & subwings) :
        linkNode(linkNode), icorridors(icorridors), xcorridors(xcorridors), subwings(subwings)
    {
        set<unsigned> halls_set;

        if (linkNode != 0)
        {
            halls_set.insert(linkNode);
        }

        for (unsigned i = 0; i < icorridors.size(); ++i)
        {
            halls_set.insert(icorridors[i].a);
            halls_set.insert(icorridors[i].b);
        }

        for (unsigned i = 0; i < xcorridors.size(); ++i)
        {
            halls_set.insert(xcorridors[i].a);
        }

        halls.assign(halls_set.begin(), halls_set.end());

        if (false)
        if (halls.size() != nHalls)
        {
            // NOTE: nHalls is superfluous -- except in the "1 0 0" case
            cout << "counted halls: " << halls.size() << " while nHalls: " << nHalls << endl;
            for (unsigned u : halls_set)
            {
                cout << " " << u << endl;
            }
            assert(halls.size() == nHalls);
        }
    }

    unsigned linkNode;
    vector<unsigned> halls;

    vector<Corridor> icorridors; // internal corridors
    vector<Corridor> xcorridors; // external corridors (to subwings)
    vector<Wing> subwings;
};

Wing readwing(istream & is, const unsigned & linkNode)
{
    unsigned nHalls, nCorridors, nSubwings;

    is >> nHalls >> nCorridors >> nSubwings;

    if (!is)
    {
        throw runtime_error("end of input");
    }

    //cout << "readwing: " << nHalls << " " << nCorridors << " " << nSubwings << endl;

    vector<Corridor> icorridors;
    while (icorridors.size() < nCorridors)
    {
        unsigned a, b;
        is >> a >> b;
        icorridors.push_back(Corridor(a, b));
    }

    vector<Corridor> xcorridors;
    vector<Wing> subwings;

    while (subwings.size() < nSubwings)
    {
        unsigned a, b;
        is >> a >> b;
        xcorridors.push_back(Corridor(a, b));
        Wing subwing = readwing(is, b);
        subwings.push_back(subwing);
    }

    return Wing(nHalls, linkNode, icorridors, xcorridors, subwings);
}

void check_wing_solutions (
        const unsigned & guards,
        const unsigned & linkNode,
        const bool     & linkNodeGuarded,
        const vector<unsigned>::const_iterator & hall_curr,
        const vector<unsigned>::const_iterator & hall_end,
        const vector<Corridor> & icorridors,
        const vector<unsigned> & xcorridor_extra,
        unsigned & best_guarded,
        unsigned & best_unrestricted
    )
{
    if (hall_curr != hall_end)
    {
        // Recurse if we DON'T put a guard on this node
        check_wing_solutions(
                guards,
                linkNode,
                linkNodeGuarded,
                hall_curr + 1,
                hall_end,
                icorridors,
                xcorridor_extra,
                best_guarded,
                best_unrestricted
            );

        // Recurse if we DO put a guard on this node
        const unsigned & curr = *hall_curr;

        vector<Corridor> new_icorridors;
        for (auto & icorridor : icorridors)
        {
            if (!(icorridor.a == curr || icorridor.b == curr))
            {
                new_icorridors.push_back(icorridor); // if the 'curr' node doesn't watch this icorridor, keep it.
            }
        }

        vector<unsigned> new_xcorridor_extra;
        for (auto & xc : xcorridor_extra)
        {
            if (xc != curr)
            {
                new_xcorridor_extra.push_back(xc); // if the 'curr' node doesn't watch this xcorridor, keep it.
            }
        }

        check_wing_solutions(
                guards + 1,
                linkNode,
                linkNodeGuarded || (curr == linkNode),
                hall_curr + 1,
                hall_end,
                new_icorridors,
                new_xcorridor_extra,
                best_guarded,
                best_unrestricted
            );
    }
    else // all nodes are now either guarded or not. Count the cost.
    {
        if (icorridors.empty())
        {
            // If we cover all INTERNAL nodes of this wing, we have a valid solution.

            const unsigned total_guards = guards + xcorridor_extra.size();

            best_unrestricted = min(best_unrestricted, total_guards);

            if (linkNodeGuarded)
            {
                best_guarded = min(best_guarded, total_guards);
            }
        }
    }
}

void solve_wing(const Wing & wing, unsigned & count_if_linkNode_guarded, unsigned & count_if_linkNode_unrestricted)
{
    // For each of the subwings, we solve recursively.

    vector<unsigned> xcorridor_extra;

    unsigned guards = 0;

    for (unsigned i = 0; i < wing.subwings.size(); ++i)
    {
        unsigned cost_guarded;
        unsigned cost_unrestricted;

        solve_wing(wing.subwings[i], cost_guarded, cost_unrestricted);

        guards += cost_unrestricted;

        assert(cost_guarded == cost_unrestricted || cost_guarded == cost_unrestricted + 1);

        if (cost_guarded > cost_unrestricted)
        {
            xcorridor_extra.push_back(wing.xcorridors[i].a);
        }
    }

    count_if_linkNode_guarded      = 1000000000;
    count_if_linkNode_unrestricted = 1000000000;

    check_wing_solutions (
            guards,
            wing.linkNode,
            false,
            wing.halls.begin(), wing.halls.end(),
            wing.icorridors,
            xcorridor_extra,
            count_if_linkNode_guarded,
            count_if_linkNode_unrestricted
        );
}

int main()
{
    for (;;)
    {
        try
        {
            Wing castle = readwing(cin, 0);

            unsigned best_guarded;
            unsigned best_unrestricted;

            solve_wing(castle, best_guarded, best_unrestricted);
            cout << best_unrestricted << endl;
        }
        catch (const runtime_error &)
        {
            break;
        }
    }

    return 0;
}
