#include "measurement/Benchmark.h"
#include "core/UniversalSorter.h"

Benchmark::Benchmark(double a, double b, double c, int seed, int costThreshold)
    : timer(), a(a), b(b), c(c), seed(seed), costThreshold(costThreshold) {}

void Benchmark::run(Vector& V) {
    timer.start();

    // Cria o UniversalSorter
    UniversalSorter sorter(V);

    // Calcula o número de quebras
    int numBreaks = V.getNumBreaks();
    std::cout << "size " << V.getCurrentSize() << " seed " << seed << " breaks " << numBreaks << "\n\n";

    // Determina o tamanho mínimo de partição
    int minPartitionSize = sorter.determinePartitionThreshold(costThreshold, a, b, c);

    // Ordena o vetor
    Statistics stats;
    sorter.sort(V, minPartitionSize, V.getNumBreaks(), stats);

    // Calcula o limiar de quebras
    sorter.determineBreaksThreshold(seed, costThreshold, minPartitionSize, a, b, c);

    timer.stop();

    // Imprime o tempo decorrido
    std::cout << "Tempo decorrido: " << timer.elapsedSeconds() << " segundos\n";

    // Imprime o vetor ordenado
    std::cout << "Vetor ordenado:\n";
    V.print();
}