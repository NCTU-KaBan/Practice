// Programming language: C99
// @EXPECTED_RESULTS@: CORRECT

/*
 * This program is a bit more complicated than necessary, because
 * it was designed to solve the original version of the problem where
 * the bicycle had a limited maximum speed.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


#define MIN_DISTANCE    1.0
#define MAX_DISTANCE    10000.0
#define MAX_LIGHT       10
#define MIN_PERIOD      10.0
#define MAX_PERIOD      500.0

/*
 * Maximum duration of trip:
 *   10 traffic lights at regular spacing
 *   11 segments of 910 meter, traveled at max acceleration 
 *     = 11 * sqrt(2 * 910) = 470 seconds
 *   plus 10 traffic lights, each red for 500 seconds = 5000 seconds
 *
 * Total duration less than 6000 seconds.
 * Each traffic light can cycle less than 6000 / (10 + 10) = 300 times.
 */
#define MAX_CYCLE    1024


const double vmax = 1000;    /* maximum speed */
const double amax = 0.5;    /* maximum acceleration */
double xdest;            /* trip distance */
int    nlight;            /* number of traffic lights */

struct {
    double x;    /* position of traffic light */
    double red;    /* red period of traffic light */
    double green;    /* green period of traffic light */
} light[MAX_LIGHT];


/*
 * speed[i][k] = Maximum possible speed while passing traffic light i
 *               at the moment it turns red for the k)-th time since
 *               the start of the trip;
 *               Or -1 if it is not possible to reach light i by the
 *               k)-th time it turns red.
 */
double    speed[MAX_LIGHT][MAX_CYCLE];


/*
 * Return the minimum time needed to travel distance dX with action Q.
 *
 * If (Q <= 0), start at initial speed Q, then accelerate up to vmax.
 * If (Q <= 0), stop and wait for (-Q) seconds, then accelerate up to vmax.
 */
double find_dt(double dx, double q)
{
    assert(dx > 0);
    assert(q <= vmax);

    double v = (q > 0) ? q : 0;

    /* calculate time and distance after accelerating to vmax. */
    double vmax_dt = (vmax - v) / amax;
    double vmax_dx = v * vmax_dt + 0.5 * amax * vmax_dt * vmax_dt;

    double dt;
    if (vmax_dx > dx) {
        /* continuous max acceleration */
        dt = sqrt(v * v + 2 * amax * dx) / amax - v / amax;
    } else {
        /* max acceleration until vmax, then constant speed */
        dt = vmax_dt + (dx - vmax_dx) / vmax;
    }

    return (q < 0) ? (dt - q) : dt;
}


/*
 * Calculate the action that needs to be taken in order to travel
 * distance dx in time interval exactly dt.
 *
 * Return V if the proper action is to start at initial speed V,
 * followed by maximum acceleration up to vmax, followed by constant speed.
 *
 * Return (-T) if the proper action is to wait for duration T at zero speed,
 * followed by maximum acceleration up to vmax, followed by constant speed.
 */
double find_q(double dx, double dt)
{
    assert(dx > 0);
    assert(dt > 0);
    assert(dx <= vmax * dt);

    /* Calculate time needed to travel dx when starting from zero speed. */
    double tt = sqrt(2 * dx / amax);
    if (tt * amax > vmax)
        tt = 0.5 * vmax / amax + dx / vmax;
    if (tt < dt)
        return tt - dt;

    /* Calculate initial speed Q, assuming continuous acceleration. */
    double q = dx / dt - 0.5 * amax * dt;
    if (q + dt * amax > vmax) {
        /* Calculate intial speed, assuming acceleration up to vmax. */
        q = vmax - sqrt(2 * amax * (vmax * dt - dx));
    }
    return q;
}


/*
 * We are currently in state (x, t).
 *
 * We are allowed to take any action between qmax and qmin in order to get
 * to the next traffic light or to the end of the trip.
 *
 * A positive value of Q means to move ahead immediately at speed Q
 * with max acceleration.
 *
 * A negative value of Q means to make a full stop, stand still for -Q seconds,
 * then move ahead at max acceleration.
 */
void scan_forward_qrange(double x, double t, double qmax, double qmin, int i,
             double *answer)
{
    if (i == nlight) {

        /* No more traffic lights, just get to the end as quickly
           as possible. */
        double dt = find_dt(xdest - x, qmax);
        if (t + dt < *answer)
            *answer = t + dt;

    } else {

        /* Distance to cover in this step. */
        double dx = light[i].x - x;
        assert(dx > 0);

        /* Find the earliest possible arrival time at light i. */
        double tmin = t + find_dt(dx, qmax);

        /* Find the latest possible arrival time at light i. */
        double tmax = t + find_dt(dx, qmin);

        /* Consider all green-light periods of traffic light i which
           have partial overlap with range tmin .. tmax. */
        double cycle_time = light[i].red + light[i].green;

        for (int k = (int)(tmin / cycle_time);
             k * cycle_time <= tmax && k * cycle_time <= *answer;
             k++) {

            assert(k + 1 < MAX_CYCLE);

            /* Consider the (k+1)-th green-light period. */
            double green_start = k * cycle_time + light[i].red;
            double green_end   = (k + 1) * cycle_time;

            if (green_end <= tmax) {
                /* We can reach this traffic light at the
                   exact moment when it turns red.
                   Find the speed with which we would arrive. */
                double q = find_q(dx, green_end - t);
                double v = (q > 0) ? q : 0;
                v += amax * find_dt(dx, v);
                if (v > vmax)
                    v = vmax;
                /* Remember the fact that we can reach this
                   point in space-time at this speed. */
                if (v > speed[i][k+1])
                    speed[i][k+1] = v;
            }

            /* Calculate the Q subrange corresponding to (part of)
               this green-light period. */
            if (green_start <= tmax) {
                double qsub_max = qmax;
                double qsub_min = qmin;
                if (green_start > tmin)
                    qsub_max = find_q(dx, green_start - t);
                if (green_end < tmax)
                    qsub_min = find_q(dx, green_end - t);

                /* Recursive call to project this subrange
                   onto further traffic lights. */
                scan_forward_qrange(x, t,
                                    qsub_max, qsub_min,
                                    i + 1, answer);
            }

        }

    }
}


/*
 * Project forward from state (x, t, v) towards traffic lights i and further
 * and towards the final answer.
 */
void go_forward(double x, double t, double v, int i, double *answer)
{
    /* Initialize action window.
       The most forward directed action we can take is to
       maintain current speed and charge ahead. */
    double qmax = v;

    /* The most backward directed action we can take is to
       make a full stop and wait until everything is over. */
    double qmin = - *answer;

    /* Look forward through this window to the following
       traffic lights. */
    scan_forward_qrange(x, t, qmax, qmin, i, answer);
}


double solve(void)
{
    double x;

    /* Initialize all traffic lights to be unreachable at all times. */
    for (int i = 0; i < nlight; i++)
        for (int k = 0; k < MAX_CYCLE; k++)
            speed[i][k] = -1;

    /*
     * Calculate an upper bound on the duration of the trip:
     *   full stop at each traffic light;
     *   wait until it turns green;
     *   travel at max acceleration/speed to next traffic light.
     */
    double answer = 0;
    x = 0;
    for (int i = 0; i < nlight; i++) {
        answer += find_dt(light[i].x - x, 0);
        answer += light[i].red;
        x = light[i].x;
    }
    answer += find_dt(xdest - x, 0);

    /* Consider starting point of trip (x=0, t=0, v=0) and project
       forward towards traffic lights and towards the final answer. */
    go_forward(0, 0, 0, 0, &answer);

    /* Consider each traffic light. */
    for (int i = 0; i < nlight; i++) {
        double cycle_time = light[i].red + light[i].green;
        for (int k = 0; k * cycle_time <= answer; k++) {
            assert(k < MAX_CYCLE);

            /* Consider reaching this traffic light just
               as it turns red for the k-th time.
               The bike is then in a specific state (x, v, t).
               Project forward from that state towards further
               traffic ligts and towards the final answer. */
            if (speed[i][k] >= 0)
                go_forward(light[i].x,
                           k * cycle_time,
                           speed[i][k],
                       i + 1,
                       &answer);
        }
    }

    /* In the end, we will have found the lowest possible trip time. */
    return answer;
}


int main(void)
{
next_case:

    if (scanf("%lf %d", &xdest, &nlight) != 2)
        return 0;

    assert(xdest >= MIN_DISTANCE && xdest <= MAX_DISTANCE);
    assert(nlight >= 0 && nlight <= MAX_LIGHT);

    for (int i = 0; i < nlight; i++) {
        scanf("%lf %lf %lf", &light[i].x,
                             &light[i].red,
                             &light[i].green);
        assert(light[i].x > 0 && light[i].x < xdest);
        assert(i == 0 || light[i].x > light[i-1].x);
        assert(light[i].red   >= MIN_PERIOD &&
               light[i].red   <= MAX_PERIOD);
        assert(light[i].green >= MIN_PERIOD &&
               light[i].green <= MAX_PERIOD);
    }

    double answer = solve();
    printf("%.3f\n", answer);

    goto next_case;
}

/* end */
