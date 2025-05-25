#include "measurement/Benchmark.h"
#include "core/UniversalSorter.h"  
#include "datastructures/Vector.h" 
#include <iostream>                

Benchmark::Benchmark(double a, double b, double c, int seed, double costThreshold)
    : timer(), a(a), b(b), c(c), seed(seed), costThreshold(costThreshold) {}

void Benchmark::run(Vector& V) { 
    if (V.getCurrentSize() == 0) {
        std::cout << "size 0 seed " << seed << " breaks 0\n\n";
        std::cout << "INFO: Vetor de entrada está vazio. Nada a fazer no benchmark." << std::endl;

        // * Inicializa o UniversalSorter e Statistics finais
        UniversalSorter sorter;
        Statistics finalSortStats;
        sorter.adaptiveSort(V, seed, costThreshold, a, b, c, finalSortStats); 
        return;
    }

    timer.start();

    UniversalSorter sorter;
    Statistics finalSortStats; //* Para receber as estatísticas da ordenação final de adaptiveSort

    //* Imprime informações iniciais sobre o vetor de entrada
    int initialBreaks = V.getNumBreaks();
    std::cout << "size " << V.getCurrentSize() << " seed " << seed << " breaks " << initialBreaks << "\n\n";

    //* Chama o método de ordenação adaptativa.
    //* Este método cuidará da calibração (usando o cache ou realizando nova calibração)
    //* e da ordenação final do vetor V.
    sorter.adaptiveSort(V, seed, costThreshold, a, b, c, finalSortStats);
    //* Após esta chamada, V estará ordenado e finalSortStats conterá as estatísticas da ordenação principal.

    timer.stop();

    // * Se quiser saber tempo do benchmark, so descomentar a linha abaixo
    //std::cout << "\nTempo total do benchmark (incluindo calibração, se feita, e ordenação): " << timer.elapsedSeconds() << " segundos." << std::endl;
}