#include "algorithms/InsertionSort.h"

void insertionSort(Vector& v, int l, int r) {

    for (int i = l + 1; i <= r; ++i) {
        int aux = v.getElement(i);

        int j = i - 1;

        while (j >= l && v.getElement(j) > aux) {
            v.setElement(j + 1, v.getElement(j));
            --j;
        }

        if (i != j + 1) {
            v.setElement(j + 1, aux);
        }
    }
}