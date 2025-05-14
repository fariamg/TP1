#include <InsertionSort.h>

void insertionSort(Vector& v, int l, int r, Statistics& stats) {
    stats.incrementFunctionCalls();

    for (int i = l + 1; i <= r; ++i) {
        int aux = v.getElement(i);
        stats.incrementMovements();

        int j = i - 1;

        while (j >= l && v.getElement(j) > aux) {
            stats.incrementComparisons();
            v.setElement(j + 1, v.getElement(j)); 
            stats.incrementMovements();
            --j;
        }
        stats.incrementComparisons();

        if (i != j + 1) {
            v.setElement(j + 1, aux); 
            stats.incrementMovements();
        }
    }
}