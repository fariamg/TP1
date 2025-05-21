#include <chrono>
#include <iomanip>
#include <iostream>

#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "core/UniversalSorter.h"
#include "datastructures/Vector.h"
#include "measurement/Statistics.h"

int main() {
    // int size = 10;
    // Vector v(size);
    // Statistics stats;

    // std::cout << "TESTE INSERTION SORT\n";

    // // Preencher o vetor com números aleatórios
    // for (int i = 0; i < size; ++i) {
    //     v.push_back(rand() % 10000);
    // }

    // v.print();
    // std::cout << "------------------------\n";

    // //Medir o tempo de execução do Insertion Sort
    // auto start = std::chrono::high_resolution_clock::now();
    // insertionSort(v, 0, size - 1, stats);
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed = end - start;

    // std::cout << "Insertion Sort took: " << elapsed.count() << " seconds\n";
    // std::cout << "Function calls: " << stats.getFunctionCalls() << "\n";
    // std::cout << "Comparisons: " << stats.getComparisons() << "\n";
    // std::cout << "Movements: " << stats.getMovements() << "\n";

    // std::cout << "------------------------\n";

    // v.print();

    // std::cout << "------------------------\n";

    // std::cout << "TESTE QUICK SORT\n";
    // Vector v2(size);
    // Statistics stats2;

    // for (int i = 0; i < size; ++i) {
    //     v2.push_back(rand() % 10000);
    // }

    // v2.print();

    // std::cout << "------------------------\n";

    // //Medir o tempo de execução do Quick Sort
    // auto start2 = std::chrono::high_resolution_clock::now();
    // quickSort(v2, 2, 0, size - 1, stats2);
    // auto end2 = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> elapsed2 = end2 - start2;

    // std::cout << "Quick Sort took: " << elapsed2.count() << " seconds\n";
    // std::cout << "Function calls: " << stats2.getFunctionCalls() << "\n";
    // std::cout << "Comparisons: " << stats2.getComparisons() << "\n";
    // std::cout << "Movements: " << stats2.getMovements() << "\n";
    // std::cout << "------------------------\n";

    // v2.print();

    // std::cout << "------------------------\n";

    // std::cout << "TESTE QUEBRAS\n";

    // Vector v3(10);
    // v3.push_back(1);
    // v3.push_back(3);
    // v3.push_back(2);
    // v3.push_back(4);

    // std::cout << "Número de quebras: " << v3.getNumBreaks() << "\n";

    // // Lê os parâmetros de entrada
    // double limiarCusto;
    // double coefA, coefB, coefC;
    // int tam;

    // std::cin >> limiarCusto >> coefA >> coefB >> coefC >> tam;

    // // Inicializa o vetor com valores aleatórios
    // Vector v4(tam);
    // for (int i = 0; i < tam; ++i) {
    //     v4.push_back(rand() % 10000); // Preenche com números aleatórios
    // }

    // // Cria o UniversalSorter
    // UniversalSorter sorter(tam);

    // // Determina o limiar de partição
    // int limiarParticao = sorter.determinePartitionThreshold(limiarCusto);

    // // Imprime os resultados no formato esperado
    // std::cout << "size " << tam << " seed 1 breaks " << v.getNumBreaks() << "\n";

    // int iter = 0;
    // while (true) {
    //     std::cout << "iter " << iter << "\n";

    //     // Simula os valores de mps e custos para cada iteração
    //     for (int i = 0; i < 6; ++i) {
    //         int mps = 2 + i * (tam / 5); // Exemplo de cálculo de mps
    //         double cost =
    //             coefA * sorter.getStats().getComparisons() + coefB * sorter.getStats().getMovements() + coefC *
    //             sorter.getStats().getFunctionCalls();

    //         std::cout << "mps " << mps << " cost " << std::fixed << std::setprecision(9) << cost << " cmp " << sorter.getStats().getComparisons()
    //                   << " move " << sorter.getStats().getMovements() << " calls " << sorter.getStats().getFunctionCalls() << "\n";
    //     }

    //     // Exemplo de valores finais da iteração
    //     std::cout << "nummps 6 limParticao " << limiarParticao << " mpsdiff 0.0\n";

    //     // Condição de parada (exemplo)
    //     if (iter >= 3)
    //         break;
    //     ++iter;
    // }

    // Define os parâmetros para o teste
    //     int vectorCapacity = 100;         // Tamanho do vetor
    //     int costThreshold = 10;           // Limiar de custo
    //     double a = 1.0, b = 1.0, c = 1.0; // Parâmetros para calcular o custo

    //     Vector V(vectorCapacity); // Cria o vetor com o tamanho definido

    //     // Preenche o vetor com números aleatórios
    //     for (int i = 0; i < vectorCapacity; ++i) {
    //         V.push_back(rand() % 10000); // Preenche com números aleatórios
    //     }

    //     // Cria o objeto UniversalSorter
    //     UniversalSorter sorter(V);

    //     // Imprime o vetor inicial
    //     std::cout << "Vetor inicial:\n";

    //     // Determina o limiar de partição
    //     int partitionThreshold = sorter.determinePartitionThreshold(costThreshold, a, b, c);

    //     // Imprime o resultado
    //     std::cout << "Limiar de partição determinado: " << partitionThreshold << "\n";

    //     // Imprime o vetor após a ordenação
    //     std::cout << "Vetor após a ordenação:\n";
    //     sorter.V.print();

    //     return 0;
    int seed = 42;            // Semente para embaralhamento
    int costThreshold = 10;   // Limiar de custo
    int minPartitionSize = 5; // Tamanho mínimo de partição
    int a = 1, b = 1, c = 1;  // Pesos para cálculo de custo
    int vectorSize = 100;     // Tamanho do vetor

    // Inicializa o gerador de números aleatórios
    std::srand(seed);

    // Cria o vetor e preenche com valores aleatórios
    Vector V(vectorSize);
    for (int i = 0; i < vectorSize; ++i) {
        V.push_back(i); // Valores aleatórios entre 0 e 99
    }

    // Imprime o vetor inicial
    std::cout << "Vetor inicial:\n";
    V.print();

    // Cria o UniversalSorter
    UniversalSorter sorter(V);

    // Calcula o limiar de quebras
    int breaksThreshold = sorter.determineBreaksThreshold(seed, costThreshold, minPartitionSize, a, b, c);

    // Imprime o resultado
    std::cout << "\nLimiar de quebras determinado: " << breaksThreshold << "\n";

    return 0;
}