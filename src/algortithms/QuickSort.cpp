#include <QuickSort.h>

void partition3(Vector& v, int l, int r, int& i, int& j, Statistics& stats) {
    stats.incrementFunctionCalls(1);

    i = l;
    j = r;

    int pivot = median(v.getElement(l), v.getElement(r), v.getElement((l + r) / 2));

    do {
        while (v.getElement(i) < pivot) {
            ++i;
            stats.incrementComparisons(1);
        }
        stats.incrementComparisons(1);

        while (v.getElement(j) > pivot) {
            --j;
            stats.incrementComparisons(1);
        }
        stats.incrementComparisons(1);

        if (i <= j) {
            v.setElement(i, v.getElement(j));
            v.setElement(j, v.getElement(i));
            ++i;
            --j;
            stats.incrementMovements(2);
        }
    } while (i <= j);
}

int median(int a, int b, int c) {
    if ((a <= b) && (b <= c))
        return b;
    if ((a <= c) && (c <= b))
        return c;
    if ((b <= a) && (a <= c))
        return a;
    if ((b <= c) && (c <= a))
        return c;
    if ((c <= a) && (a <= b))
        return a;
    return b;
}