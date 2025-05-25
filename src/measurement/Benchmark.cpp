#include "measurement/Benchmark.h"
#include "core/UniversalSorter.h"  // Para UniversalSorter e Statistics
#include "datastructures/Vector.h" // Para Vector
#include <iostream>                // Para std::cout

Benchmark::Benchmark(double a, double b, double c, int seed, double costThreshold)
    : timer(), a(a), b(b), c(c), seed(seed), costThreshold(costThreshold) {}

void Benchmark::run(Vector& V) { // V é o vetor original do arquivo
    if (V.getCurrentSize() == 0) {
        std::cout << "size 0 seed " << seed << " breaks 0\n\n";
        std::cout << "INFO: Vetor de entrada está vazio. Nada a fazer no benchmark." << std::endl;
        // A lógica de adaptiveSort já imprime uma mensagem para vetor vazio,
        // mas podemos adicionar uma aqui também se quisermos que o benchmark reporte.
        // Se adaptiveSort for chamado, ele também lidará com isso.
        UniversalSorter sorter;
        Statistics finalSortStats;
        sorter.adaptiveSort(V, seed, costThreshold, a, b, c, finalSortStats); // Deixa adaptiveSort lidar com o vetor vazio
        return;
    }

    timer.start();

    UniversalSorter sorter;
    Statistics finalSortStats; // Para receber as estatísticas da ordenação final de adaptiveSort

    // Imprime informações iniciais sobre o vetor de entrada
    int initialBreaks = V.getNumBreaks(); // Calcula quebras antes de qualquer modificação/cópia por adaptiveSort
    std::cout << "size " << V.getCurrentSize() << " seed " << seed << " breaks " << initialBreaks << "\n\n";

    // Chama o método de ordenação adaptativa.
    // Este método cuidará da calibração (usando o cache ou realizando nova calibração)
    // e da ordenação final do vetor V.
    sorter.adaptiveSort(V, seed, costThreshold, a, b, c, finalSortStats);
    // Após esta chamada, V estará ordenado e finalSortStats conterá as estatísticas da ordenação principal.

    timer.stop();

    // A saída das estatísticas da ordenação (CMP, MOV, Custo, etc.) já é feita
    // dentro de adaptiveSort. Se você quiser imprimir algo adicional aqui, pode fazer.
    // Por exemplo, o tempo total do benchmark:
    std::cout << "\nTempo total do benchmark (incluindo calibração, se feita, e ordenação): " << timer.elapsedSeconds() << " segundos." << std::endl;

    // Se você quiser verificar se o vetor está ordenado (para fins de depuração do benchmark):
    // if (!V.isSorted()) {
    //     std::cerr << "ERRO DE BENCHMARK: Vetor NÃO está ordenado após adaptiveSort!" << std::endl;
    // } else {
    //     std::cout << "INFO DE BENCHMARK: Vetor está ordenado após adaptiveSort." << std::endl;
    // }
}