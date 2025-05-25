#include "algorithms/QuickSort.h"
#include "algorithms/InsertionSort.h"

int median(int a, int b, int c);

void partition(Vector& V, int l, int r, int& i, int& j, Statistics& stats);

void quickSort(Vector& V, int partitionSize, int l, int r, Statistics& stats) {
    stats.setAlgorithmName("qs");

    stats.incrementFunctionCalls(1); // Incrementa chamadas de função

    // Caso base
    if (l >= r)
        return;

    int i = 0, j = 0;

    // Primeira partição
    partition(V, l, r, i, j, stats);

    // Partições recursivas, com verificação para o insertion sort
    if (l < j) {
        if ((j - l) < partitionSize) {
            insertionSort(V, l, j, stats); // Usa insertionSort com estatísticas
        } else {
            quickSort(V, partitionSize, l, j, stats);
        }
    }

    if (i < r) {
        if ((r - i) < partitionSize) {
            insertionSort(V, i, r, stats); // Usa insertionSort com estatísticas
        } else {
            quickSort(V, partitionSize, i, r, stats);
        }
    }
}

void partition(Vector& V, int l, int r, int& i, int& j, Statistics& stats) {
    stats.incrementFunctionCalls(1); // Incrementa chamadas de função

    // Escolhe o pivô, sendo o médio do primeiro, último e elemento do meio.
    i = l;
    j = r;
    int pivot = median(V.getElement(l), V.getElement(r), V.getElement((l + r) / 2));

    // Anda com i e j até encontrar os elementos que devem ser trocados
    do {
        while (V.getElement(i) < pivot) {
            stats.incrementComparisons(1); // Incrementa comparações
            i++;
        }
        stats.incrementComparisons(1); // Incrementa comparações

        while (V.getElement(j) > pivot) {
            stats.incrementComparisons(1); // Incrementa comparações
            j--;
        }
        stats.incrementComparisons(1); // Incrementa comparações

        // Se eles não se cruzaram ainda, faz a troca e anda +1 posição com i e j.
        if (i <= j) {
            V.swap(i, j);
            stats.incrementMovements(3); // Incrementa movimentações (swap conta como 3 movimentos)
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
