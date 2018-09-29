// @EXPECTED_RESULTS@: CORRECT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define MAX_PUBS    5
#define MAX_STUDENTS    50


/*
 *  prob_yield[P][K][I] =
 *    Probability that out of K votes distributed to pubs P .. (N-1),
 *    precisely I votes are taken by pub P.
 */
double prob_yield[MAX_PUBS][MAX_STUDENTS+1][MAX_STUDENTS+1];

/*
 *  prob_nvote[P][K][V][R] =
 *    Probability that for K votes distributed to pubs P .. (N-1),
 *    no pub ends up with more than V votes, while (R+1) pubs end up
 *    with exactly V votes.
 */
double prob_nvote[MAX_PUBS][MAX_STUDENTS+1][MAX_STUDENTS+1][MAX_PUBS];


/*
 * Assume two pubs.
 *
 * Given
 *   va = initial number of votes for pub A,
 *   vb = initial number of votes for pub B,
 *   k  = maximum number of votes to cast,
 *
 * Calculate
 *   (*yield)[kk][i] =
 *     probability that precisely i out of kk votes are for pub A.
 */
void calc_prob_yield(int va, int vb, int k, double (*yield)[MAX_STUDENTS+1][MAX_STUDENTS+1])
{
    assert(k >= va + vb);

    /* Initialize result array. */
    for (int q = 0; q <= k; q++)
        for (int i = 0; i <= k; i++)
            (*yield)[q][i] = 0;

    /* After va + vb votes are cast, we are certain that exactly va
       votes are for pub A. */
    (*yield)[va+vb][va] = 1;

    for (int q = va + vb; q < k; q++) {

        /*
         * Update probabilities to account for next vote:
         *   prob_new[i] = prob[i-1] * (i-1) / q + prob[i] * (q-i) / q
         */
        for (int i = 1; i <= q; i++)
            (*yield)[q+1][i] =
                ( (*yield)[q][i-1] * (i - 1) +
                  (*yield)[q][i] * (q - i) ) / (double)q;
        (*yield)[q+1][q+1] = (*yield)[q][q];

    }

}


/*
 * Initialize prob_nvote[i], assuming that the next pub after i is j.
 * If j == -1, assume that i is the last pub which gets votes.
 */
void calc_prob_nvote(int n, int k, int i, int j, int allowmore)
{

    /* Clear results. */
    for (int q = 0; q <= k; q++)
        for (int v = 0; v <= k; v++)
            for (int r = 0; r < MAX_PUBS; r++)
                prob_nvote[i][q][v][r] = 0;

    if (j < 0) {

        /* This is the last pub; it takes all remaining votes. */
        for (int q = 0; q <= k; q++)
            prob_nvote[i][q][q][0] = 1;

    } else {

        /* Build table for pub I based on table for pub J. */
        for (int q = 0; q <= k; q++) {
            for (int v = 0; v <= q; v++) {
                /* Consider the case where pub I has V votes
                   and some other pub also has V votes. */
                for (int r = 1; r < n; r++)
                    prob_nvote[i][q][v][r] += prob_yield[i][q][v] * prob_nvote[j][q-v][v][r-1];
                /* Consider the case where pub I has V votes
                   and all other pubs have fewer votes. */
                for (int t = 0; t < v && t <= q - v; t++)
                    for (int r = 0; r < n; r++)
                        prob_nvote[i][q][v][0] += prob_yield[i][q][v] * prob_nvote[j][q-v][t][r];
                if (allowmore) {
                    /* Consider the case where pub I has V votes
                       and some other pub has more than V votes. */
                    for (int t = v + 1; t <= q - v; t++)
                        for (int r = 0; r < n; r++)
                            prob_nvote[i][q][t][r] += prob_yield[i][q][v] * prob_nvote[j][q-v][t][r];
                }
            }
        }

    }
}



/* Calculate the probability that pub P wins the vote. */
double calc_pub_win_prob(int n, int k, const int *votes, int p)
{
    /* Initialze yield tables, assuming pub P gets first votes. */
    int q = 0;
    for (int i = 0; i < n; i++)
        q += votes[i];
    q -= votes[p];
    calc_prob_yield(votes[p], q, k, &prob_yield[p]);
    for (int i = 0; i < n; i++) {
        if (i != p) {
            q -= votes[i];
            calc_prob_yield(votes[i], q, k, &prob_yield[i]);
        }
    }

    /* Initialize nvote table, assuming P gets first votes. */
    int j = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (i != p) {
            calc_prob_nvote(n, k, i, j, 1);
            j = i;
        }
    }
    calc_prob_nvote(n, k, p, j, 0);

    /* Add up all probabilities where pub P wins. */
    double winprob = 0;
    for (int v = 0; v <= k; v++) {
        winprob += prob_nvote[p][k][v][0];
        for (int r = 1; r < n; r++)
            winprob += prob_nvote[p][k][v][r] / (double)(r + 1);
    }

    return winprob;
}


/* Calculate winning probability of each pub. */
void solve(int n, int k, const int *votes)
{
    for (int p = 0; p < n; p++) {
        double winprob = calc_pub_win_prob(n, k, votes, p);
        printf("pub %d: %.2f %%\n", p + 1, 100.0 * winprob);
    }
}


int main(void)
{
    int votes[MAX_PUBS];

    for (;;) {
        int n, k;

        if (scanf("%d %d", &n, &k) != 2) break;

        assert(n >= 1 && n <= MAX_PUBS);
        assert(k >= 1 && k <= MAX_STUDENTS);

        int sumv = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", votes + j);
            assert(votes[j] >= 1);
            sumv += votes[j];
        }
        assert(sumv <= k);

        solve(n, k, votes);
    }

    return 0;
}

/* end */
