#include "algorithms/QuickSort.h"
#include "algorithms/InsertionSort.h"

int median(int a, int b, int c);

void partition(Vector& V, int l, int r, int& i, int& j, Statistics& stats);

void quickSort(Vector& V, int partitionSize, int l, int r, Statistics& stats) {
    stats.setAlgorithmName("qs");

    stats.incrementFunctionCalls(1); 

    if (l >= r)
        return;

    int i = 0, j = 0;

    partition(V, l, r, i, j, stats);

    if (l < j) {
        if ((j - l) < partitionSize) {
            insertionSort(V, l, j, stats);
        } else {
            quickSort(V, partitionSize, l, j, stats);
        }
    }

    if (i < r) {
        if ((r - i) < partitionSize) {
            insertionSort(V, i, r, stats); 
        } else {
            quickSort(V, partitionSize, i, r, stats);
        }
    }
}

void partition(Vector& V, int l, int r, int& i, int& j, Statistics& stats) {
    stats.incrementFunctionCalls(1); 

    i = l;
    j = r;
    int pivot = median(V.getElement(l), V.getElement(r), V.getElement((l + r) / 2));

    do {
        while (V.getElement(i) < pivot) {
            stats.incrementComparisons(1); 
            i++;
        }
        stats.incrementComparisons(1); 

        while (V.getElement(j) > pivot) {
            stats.incrementComparisons(1); 
            j--;
        }
        stats.incrementComparisons(1); 

        if (i <= j) {
            V.swap(i, j);
            stats.incrementMovements(3); 
            i++;
            j--;
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
