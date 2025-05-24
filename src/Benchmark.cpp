#include "Benchmark.h"
#include "QuickSort.h"
#include "UniversalSorter.h"

Benchmark::Benchmark(double a, double b, double c, int seed, double costThreshold)
    : timer(), a(a), b(b), c(c), seed(seed), costThreshold(costThreshold) {}

void Benchmark::run(Vector& V) {
    timer.start();

    // Cria o UniversalSorter com o V original (do arquivo)
    UniversalSorter sorter(V);

    // Calcula o número de quebras no V original
    int numBreaks = V.getNumBreaks();
    std::cout << "size " << V.getCurrentSize() << " seed " << seed << " breaks " << numBreaks << "\n\n";

    std::cout << "a " << a << " b " << b << " c " << c << "\n";

    // Determina o tamanho mínimo de partição usando o V original
    int minPartitionSize = sorter.determinePartitionThreshold(costThreshold, a, b, c);

    // Ordena o vetor V (o mesmo V que foi passado por referência)
    Statistics stats;
    quickSort(V, minPartitionSize, 0, V.getCurrentSize() - 1, stats);
    // Agora V está ordenado.

    // Re-inicializa o 'sorter' com o V agora ordenado.
    // Isso faz com que o 'sorter' interno use a versão ordenada de V.
    sorter = UniversalSorter(V);

    // Calcula o limiar de quebras usando o 'sorter' que agora contém o V ordenado
    sorter.determineBreaksThreshold(seed, costThreshold, minPartitionSize, a, b, c);

    timer.stop();

    // Imprime o tempo decorrido
    // std::cout << "Tempo decorrido: " << timer.elapsedSeconds() << " segundos\n";

    // Imprime o vetor ordenado
    // std::cout << "Vetor ordenado:\n";
    // V.print();
}