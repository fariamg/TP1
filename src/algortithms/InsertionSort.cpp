#include "algorithms/InsertionSort.h"

void insertionSort(Vector& v, int l, int r, Statistics& stats) {
    stats.incrementFunctionCalls(1);

    for (int i = l + 1; i <= r; ++i) {
        int aux = v.getElement(i);
        stats.incrementMovements(1);

        int j = i - 1;

        while (j >= l && v.getElement(j) > aux) {
            stats.incrementComparisons(1);
            v.setElement(j + 1, v.getElement(j)); 
            stats.incrementMovements(1);
            --j;
        }
        stats.incrementComparisons(1);

        if (i != j + 1) {
            v.setElement(j + 1, aux); 
            stats.incrementMovements(1);
        }
    }
}