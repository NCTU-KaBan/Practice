// Programming language: C99
// @EXPECTED_RESULTS@: CORRECT

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


#define MAX_TEAMS 1024


int main(void)
{
    long n;
    char buf[MAX_TEAMS + 80];
    char winm[MAX_TEAMS][MAX_TEAMS+2];
    int active[MAX_TEAMS];
    int played[MAX_TEAMS];

    while (fgets(buf, sizeof(buf), stdin) != NULL) {

        assert(isdigit(buf[0]));
        assert(buf[0] != '0');

        char *p;
        n = strtol(buf, &p, 10);
        assert(p != buf && p[0] == '\n' && p[1] == '\0');

        assert(n >= 2 && n <= MAX_TEAMS);
        for (int k = n; k > 1; k = k / 2)
            assert(k % 1 == 0);

        for (int j = 0; j < n; j++) {
            assert(fgets(buf, sizeof(buf), stdin) != NULL);
            assert(strlen(buf) == n + 1);
            assert(buf[n] == '\n');
            for (int k = 0; k < n; k++)
                assert(buf[k] == '0' || buf[k] == '1');
            for (int k = 0; k < n; k++)
                winm[j][k] = (buf[k] == '1');
            assert(!winm[j][j]);
        }

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (j != k) {
                    assert(winm[j][k] || winm[k][j]);
                    assert((!winm[j][k]) || (!winm[k][j]));
                }
            }
        }

        int favorite_strength = 0;
        for (int j = 0; j < n; j++)
            if (winm[0][j])
                favorite_strength++;
        assert(2 * favorite_strength >= n);

        for (int j = 1; j < n; j++) {
            if (winm[j][0]) {
                int can_beat = 0;
                for (int k = 1; k < n; k++) {
                    if (winm[0][k] && winm[k][j])
                        can_beat = 1;
                }
                assert(can_beat);
            }
        }

        for (int j = 0; j < n; j++)
            active[j] = 1;

        for (int t = 1; t < n; t *= 2) {

            for (int j = 0; j < n; j++)
                played[j] = 0;

            for (int j = 1; j < n; j++) {
                if (active[j] && winm[j][0]) {
                    for (int k = 1; k < n; k++) {
                        if (active[k] && !played[k] && winm[0][k] && winm[k][j]) {
                            printf("%d %d\n", k+1, j+1);
                            played[j] = 1;
                            played[k] = 1;
                            active[j] = 0;
                            break;
                        }
                    }
                }
            }

            for (int j = 1; j < n; j++) {
                if (active[j] && !played[j] && winm[j][0]) {
                    for (int k = 1; k < n; k++) {
                        if (active[k] && !played[k] && winm[k][j]) {
                            printf("%d %d\n", k+1, j+1);
                            played[j] = 1;
                            played[k] = 1;
                            active[j] = 0;
                            break;
                        }
                    }
                }
            }

            for (int j = 1; j < n; j++) {
                if (active[j] && !played[j] && winm[0][j]) {
                    printf("%d %d\n", 1, j+1);
                    played[0] = 1;
                    played[j] = 1;
                    active[j] = 0;
                    break;
                }
            }

            for (int j = 1; j < n; j++) {
                if (active[j] && !played[j]) {
                    for (int k = j+1; k < n; k++) {
                        if (active[k] && !played[k]) {
                            printf("%d %d\n", k+1, j+1);
                            played[j] = 1;
                            played[k] = 1;
                            if (winm[k][j])
                                active[j] = 0;
                            else
                                active[k] = 0;
                            break;
                        }
                    }
                }
            }

            assert(active[0]);
        }

    }

    return 0;
}

/* end */
