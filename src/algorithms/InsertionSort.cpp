#include "algorithms/InsertionSort.h"

void insertionSort(Vector& V, int l, int r, Statistics& stats) {
    stats.setAlgorithmName("in");
    
    stats.incrementFunctionCalls(1);
    int j = 0, aux = 0;

    for (int i = l + 1; i <= r; i++) {
        stats.incrementMovements(1);
        aux = V.getElement(i);
        j = i - 1;

        while ((j >= 0) && (V.getElement(j) > aux)) {
            stats.incrementComparisons(1);
            stats.incrementMovements(1);
            V.setElement(j + 1, V.getElement(j));
            j--;
        }
        stats.incrementComparisons(1);

        if (i != j) {
            stats.incrementMovements(1);
            V.setElement(j + 1, aux);
        }
    }
    return;
}