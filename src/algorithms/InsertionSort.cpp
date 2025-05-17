#include "algorithms/InsertionSort.h"

void insertionSort(Vector& v, int size) {
    for (int i = 1; i < size; ++i) {
        int aux = v.getElement(i);
        int j = i - 1;

        while (j >= 0 && v.getElement(j) > aux) {
            v.setElement(j + 1, v.getElement(j));
            --j;
        }

        if (i != j + 1) {
            v.setElement(j + 1, aux);
        }
    }
}