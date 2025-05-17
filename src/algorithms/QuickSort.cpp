#include "algorithms/QuickSort.h"

int median(int a, int b, int c);

void partition3(Vector& v, int l, int r, int& i, int& j);

void quickSortHelper(Vector& v, int l, int r);

void quickSort(Vector& v, int size) {
    quickSortHelper(v, 0, size - 1);
}

void quickSortHelper(Vector& v, int l, int r) {
    if (l >= r)
        return;

    int i, j;
    partition3(v, l, r, i, j);

    if (l < j) {
        quickSortHelper(v, l, j);
    }

    if (i < r) {
        quickSortHelper(v, i, r);
    }
}

void partition3(Vector& v, int l, int r, int& i, int& j) {
    i = l;
    j = r;

    int pivot = median(v.getElement(l), v.getElement(r), v.getElement((l + r) / 2));

    do {
        while (v.getElement(i) < pivot) {
            ++i;
        }

        while (v.getElement(j) > pivot) {
            --j;
        }

        if (i <= j) {
            int tmp = v.getElement(i);
            v.setElement(i, v.getElement(j));
            v.setElement(j, tmp);
            ++i;
            --j;
        }
    } while (i <= j);
}

int median(int a, int b, int c) {
    if ((a <= b && b <= c) || (c <= b && b <= a))
        return b;
    if ((b <= a && a <= c) || (c <= a && a <= b))
        return a;
    return c;
}
