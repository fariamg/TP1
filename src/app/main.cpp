#include <chrono>
#include <iostream>

#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "datastructures/Vector.h"
#include "measurement/Statistics.h"

int main() {
    int size = 10;
    Vector v(size);
    Statistics stats;

    std::cout << "TESTE INSERTION SORT\n";

    // Preencher o vetor com números aleatórios
    for (int i = 0; i < size; ++i) {
        v.push_back(rand() % 10000);
    }

    v.print();
    std::cout << "------------------------\n";

    // Medir o tempo de execução do Insertion Sort
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(v, 0, size - 1, stats);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Insertion Sort took: " << elapsed.count() << " seconds\n";
    std::cout << "Function calls: " << stats.getFunctionCalls() << "\n";
    std::cout << "Comparisons: " << stats.getComparisons() << "\n";
    std::cout << "Movements: " << stats.getMovements() << "\n";

    std::cout << "------------------------\n";

    v.print();

    std::cout << "------------------------\n";

    std::cout << "TESTE QUICK SORT\n";
    Vector v2(size);
    Statistics stats2;

    for (int i = 0; i < size; ++i) {
        v2.push_back(rand() % 10000);
    }

    v2.print();

    std::cout << "------------------------\n";
    
    // Medir o tempo de execução do Quick Sort
    auto start2 = std::chrono::high_resolution_clock::now();
    quickSort(v2, 0, size - 1, stats2);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;

    std::cout << "Quick Sort took: " << elapsed2.count() << " seconds\n";
    std::cout << "Function calls: " << stats2.getFunctionCalls() << "\n";
    std::cout << "Comparisons: " << stats2.getComparisons() << "\n";
    std::cout << "Movements: " << stats2.getMovements() << "\n";
    std::cout << "------------------------\n";

    v2.print();

    return 0;
}