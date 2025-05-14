#include <Timer.h>

void clkDiff(struct timespec t1, struct timespec t2, struct timespec* res) {
    if ((t2.tv_nsec - t1.tv_nsec) < 0) {
        res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
        res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
    } else {
        res->tv_sec = t2.tv_sec - t1.tv_sec;
        res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
}