#include <algorithm>
#include <cmath>

#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "core/UniversalSorter.h"
#include "measurement/Statistics.h"

// TODO: Estou fazendo o construtor recebendo o tamanho do vetor, procurar melhor forma
UniversalSorter::UniversalSorter(Vector& V) : stats(), V(V) {}

Statistics UniversalSorter::getStats() const noexcept {
    return this->stats;
}

void UniversalSorter::sort(int minPartitionSize, int breakLimit) {
    int vectorSize = this->V.getCurrentSize();
    int vectorBreaks = this->V.getNumBreaks();

    if (vectorBreaks < breakLimit) {
        //* Vetor "quase ordenado" utiliza InsertionSort
        insertionSort(this->V, 0, vectorSize - 1, this->stats);
    } else {
        if (vectorSize > minPartitionSize) {
            //* Já se tiver muitas quebras e o tamanho do vetor for maior que o tamanho mínimo de partição usa QuickSort
            quickSort(this->V, minPartitionSize, 0, vectorSize - 1, this->stats);
        } else {
            // * Já se for menor ou igual utiliza InsertionSort (em vetores pequenos, a sobrecarga do quicksort não compensa)
            insertionSort(this->V, 0, vectorSize - 1, this->stats);
        }
    }
}

//* Os parametros são atributos do benchmark (cada benchmark pode receber valores diferentes)
int UniversalSorter::determinePartitionThreshold(int costThreshold, double a, double b, double c) {
    int minMPS = 2;                            // * Tamanhos 0 e 1 já estão ordenados
    int maxMPS = V.getCurrentSize() - 1;       // * Tamanho de partição até o tamanho maximo do vetor
    int rangeMPS = (int)(maxMPS - minMPS) / 5; // * Se V size for 100, testaremos, por exemplo: 2, 22, 42, 62, 82 e 100 ((100-2)/5 = 98/5 = 19.6 ≈ 20)

    if (rangeMPS == 0)
        rangeMPS = 1;

    int partitionThreshold = minMPS; // * Inicializa o melhor limiar de partição
    int diffCusto = 0;               // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição
    int numMPS;                      // * Numeros distintos de tamanhos de partição
    float costs[6] = {0};            // * Array para armazenar os custos dos tamanhos de partição
    int iter = 0;                // * Contador de iterações

    // ! Coloquei esse do-while para não precisar inicializar o diffCusto com um valor arbitrariamente grande
    do {
        numMPS = 0;
        std::cout << "iter " << iter << "\n";

            for (int t = minMPS; t <= maxMPS; t += rangeMPS) {
            // * Define o tamanho de partição
            this->stats.setMPS(t); 

            // * Ordena o vetor com o tamanho de partição t
            this->sort(t, V.getCurrentSize() - 1);

            // * Calcula o custo do vetor ordenado
            this->stats.calculateCost(a, b, c);

            // * Armazena o custo no array de custos
            costs[numMPS] = this->stats.getCost();

            // * Printa as estatísticas do vetor ordenado
            stats.print();

            // * Limpa as estatísticas
            this->stats.clear();

            // * Incrementa o número de tamanhos de partição
            numMPS++;
        }

        // * Printa as estatísticas de cada iteração
        this->printIterStats(numMPS, partitionThreshold, diffCusto);

        // * Calcula o menor custo entre os tamanhos de partição
        int minCostIdx = minCostIndex(costs, numMPS);

        // * Calcula o novo range de tamanhos de partição
        this->calculateNewRange(minCostIdx, minMPS, maxMPS, rangeMPS, numMPS);

        //* Calcula a diferença de custo entre os extremos
        diffCusto = costs[0] - costs[numMPS - 1];
        if (diffCusto < 0)
            diffCusto = -diffCusto; //* Valor absoluto

        iter++;

        std::cout << std::endl;
    } while ((diffCusto > costThreshold) && (numMPS >= 5));

    return partitionThreshold; // * Retorna o melhor limiar de partição
}

// ! SEED E LIMIAR DE CUSTO SÃO PARAMETROS DO BENCHMARK
//int determineBreaksThreshold(int seed, int costThreshold, int minPartitionSize) {}

void UniversalSorter::calculateNewRange(int partitionThreshold, int& minMPS, int& maxMPS, int& rangeMPS, int numMPS) {
    if (partitionThreshold == 0) {
        minMPS = 0;
        maxMPS = 2;
    } else if (partitionThreshold == numMPS - 1) {
        minMPS = numMPS - 3;
        maxMPS = numMPS - 1;
    } else {
        minMPS = partitionThreshold - 1;
        maxMPS = partitionThreshold + 1;
    }

    rangeMPS = (int)(maxMPS - minMPS) / 5;
    if (rangeMPS == 0) {
        rangeMPS++;
    }
}

int UniversalSorter:: minCostIndex(float costs[], int numMPS) {
    int minCostIndex = 0;
    for (int i = 1; i < numMPS; i++) {
        if (costs[i] < costs[minCostIndex]) {
            minCostIndex = i;
        }
    }
    return minCostIndex;
}

void UniversalSorter::printIterStats(int numMPS, int partitionThreshold, float MPSDiff) {
    std::cout << "nummps " << numMPS << " limParticao " << partitionThreshold << " mpsdiff " << MPSDiff << "\n";
}