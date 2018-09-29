
// @EXPECTED_RESULTS@: CORRECT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//#define SHOW_STUFF

#define MINV 3
#define MAXV 1000
#define MINE 3
#define MAXE 10000
#define MAXT 100

#define BIG_NUMBER (MAXE * MAXT * 2)

int nodecnt, edgecnt;
int dist[2*MAXV+1];
int route[2*MAXV+1];
int edge_src[MAXE+MAXV];
int edge_dst[MAXE+MAXV];
int edge_cost[MAXE+MAXV];
int edge_used[MAXE+MAXV];

/* Find shortest path from first node to last node. */

int findpath(void)
{
    /* mark all nodes unreachable */
    for (int i = 0; i <= nodecnt; i++)
        dist[i] = BIG_NUMBER;

    /* start in node 1 */
    dist[1] = 0;

    /* iteratively update node distances */
    for (int i = 0; i <= nodecnt; i++) {
        for (int j = 0; j < edgecnt; j++) {
            int ps, pe, pt;
            if (edge_used[j]) {
                /* shortest-path edge; must walk backwards */
                ps = edge_dst[j];
                pe = edge_src[j];
                pt = -edge_cost[j];
            } else {
                /* normal edge */
                ps = edge_src[j];
                pe = edge_dst[j];
                pt = edge_cost[j];
            }

            if (dist[ps] < BIG_NUMBER) {
                int d = dist[ps] + pt;
                if (d < dist[pe]) {
                    dist[pe] = d;
                    route[pe] = j;
                }
            }
        }
    }

    return dist[nodecnt];
}

/* Split each node into two halves with one edge in between.
   This ensures that the two paths will not share nodes. */

void split_nodes(void)
{
    /* Create a new set of nodes (nodecnt+1 ... 2*nodecnt) to act
       as the inbound side of nodes (1 ... nodecnt).
       The original nodes will only act as outbound side. */

    /* Update edges. */
    for (int i = 0; i < edgecnt; i++)
        edge_dst[i] += nodecnt;

    /* Create a new zero length edge from the inbound side of each node
       to its outbound side. */
    for (int i = 1; i <= nodecnt; i++) {
        edge_src[edgecnt] = i + nodecnt;
        edge_dst[edgecnt] = i;
        edge_cost[edgecnt] = 0;
        edgecnt++;
    }

    /* Update the total number of nodes. */
    nodecnt *= 2;
}


void show_path(void)
{
    fprintf(stderr, "path = ");
    for (int i = nodecnt; i != 1; ) {
        fprintf(stderr, " %d", i);
        int j = route[i];
        i = edge_dst[j] == i ? edge_src[j] : edge_dst[j];
    }
    fprintf(stderr, " 1\n");
}


int solve(void)
{
    /* split each node to ensure that the answer will be node-disjunct
       instead of merely edge-disjunct */
    split_nodes();

    /* mark all edges unused */
    for (int j = 0; j < edgecnt; j++)
        edge_used[j] = 0;

    /* find normal shortest path */
    int a1 = findpath();
    assert(a1 > 0);

    /* walk back from last node to first node, marking used edges */
#ifdef SHOW_STUFF
    show_path();
#endif
    for (int i = nodecnt; i != 1; ) {
        int j = route[i];
        assert(edge_dst[j] == i);
        assert(edge_used[j] == 0);
        edge_used[j] = 1;
        i = edge_src[j];
    }

    /* find second shortest path */
    int a2 = findpath();
    assert(a2 > 0);

#ifdef SHOW_STUFF
    show_path();
    fprintf(stderr, "%d %d\n", a1, a2);
#endif

    return a1 + a2;
}


int main(void)
{
    while (scanf("%d %d", &nodecnt, &edgecnt) == 2) {
        assert(nodecnt >= MINV && nodecnt <= MAXV);
        assert(edgecnt >= MINE && edgecnt <= MAXE);

        for (int i = 0; i < edgecnt; i++) {
            int ps, pe, pt;

            scanf("%d %d %d", &ps, &pe, &pt);

            assert(ps >= 1 && ps <= nodecnt);
            assert(pe >= 1 && pe <= nodecnt);
            assert(ps != pe);
            assert(pt >= 1 && pt <= MAXT);

            /* no direct edge from src to dst */
            //assert(ps != 1 || pe != nodecnt); SIDNEY: this constraint is not in the problem text

            edge_src[i] = ps;
            edge_dst[i] = pe;
            edge_cost[i] = pt;
        }

        int answer = solve();
        assert(answer < BIG_NUMBER);
        printf("%d\n", answer);
    }

    return 0;
}
