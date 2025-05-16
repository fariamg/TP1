#include "algorithms/InsertionSort.h"

int median(int a, int b, int c);

void partition3(Vector& v, int l, int r, int& i, int& j, Statistics& stats);

void quickSort(Vector& v, int l, int r, Statistics& stats) {
    stats.incrementFunctionCalls(1);

    if (l >= r)
        return;

    int i, j;

    partition3(v, l, r, i, j, stats);

    if (l < j) {
        quickSort(v, l, j, stats);
    }

    if (i < r) {
        quickSort(v, i, r, stats);
    }
}

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
            int tmp = v.getElement(i);
            stats.incrementMovements(1);
            v.setElement(i, v.getElement(j));
            stats.incrementMovements(1);
            v.setElement(j, tmp);
            ++i;
            --j;
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