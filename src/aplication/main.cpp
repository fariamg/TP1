#include <chrono>
#include <iostream>

#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "datastructures/Vector.h"
#include "measurement/Statistics.h"

int main() {
    int size = 100;
    Vector v(size);
    Statistics stats("q");

    // Preencher o vetor com números aleatórios
    for (int i = 0; i < size; ++i) {
        v.push_back(rand() % 10000);
    }

    // Medir o tempo de execução do Insertion Sort
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(v, 0, size - 1, stats);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Insertion Sort took: " << elapsed.count() << " seconds\n";
    std::cout << "Function calls: " << stats.getFunctionCalls() << "\n";
    std::cout << "Comparisons: " << stats.getComparisons() << "\n";
    std::cout << "Movements: " << stats.getMovements() << "\n";

    return 0;
}