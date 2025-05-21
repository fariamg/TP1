#include <algorithm>
#include <cmath>

#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "core/UniversalSorter.h"
#include "measurement/Statistics.h"

UniversalSorter::UniversalSorter(Vector& V) : stats(), V(V) {}

Statistics UniversalSorter::getStats() const noexcept {
    return this->stats;
}

void UniversalSorter::sort(Vector& V, int minPartitionSize, int breakLimit) {
    int vectorSize = V.getCurrentSize();
    int vectorBreaks = V.getNumBreaks();

    if (vectorBreaks < breakLimit) {
        //* Vetor "quase ordenado" utiliza InsertionSort
        insertionSort(V, 0, vectorSize - 1, this->stats);
    } else {
        if (vectorSize > minPartitionSize) {
            //* Já se tiver muitas quebras e o tamanho do vetor for maior que o tamanho mínimo de partição usa QuickSort
            quickSort(V, minPartitionSize, 0, vectorSize - 1, this->stats);
        } else {
            // * Já se for menor ou igual utiliza InsertionSort (em vetores pequenos, a sobrecarga do quicksort não compensa)
            insertionSort(V, 0, vectorSize - 1, this->stats);
        }
    }
}

//* Os parametros são atributos do benchmark (cada benchmark pode receber valores diferentes)
//* Funções relacionadas a print de estatísticas estão alocadas externamente, mantendo principios de encapsulamento
int UniversalSorter::determinePartitionThreshold(int costThreshold, double a, double b, double c) {
    int minMPS = 2;                            // * Tamanhos 0 e 1 já estão ordenados
    int maxMPS = V.getCurrentSize() - 1;       // * Tamanho de partição até o tamanho maximo do vetor
    int rangeMPS = (int)(maxMPS - minMPS) / 5; // * Se V size for 100, testaremos, por exemplo: 2, 22, 42, 62, 82 e 100 ((100-2)/5 = 98/5 = 19.6 ≈ 20)
    int numMPS;

    if (rangeMPS == 0)
        rangeMPS = 1;

    int partitionThreshold = minMPS; // * Inicializa o melhor limiar de partição
    int diffCusto = 0;               // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição
    Statistics stats[6];             // * Array para armazenar as stats de cada iteração
    int iter = 0;                    // * Contador de iterações

    // ! Coloquei esse do-while para não precisar inicializar o diffCusto com um valor arbitrariamente grande
    do {
        std::cout << "iter " << iter << "\n"; // ! Isso vai para o benchmark

        // * Zera o número do tamanho da partição
        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += rangeMPS) {
            // * Cria-se um vetor do tamanho do vetor original (desalocado após sair do escopo)
            //std::cout <<  V.getCurrentSize() << "esse é o tamanho do vetor orginial"; // ! Isso vai para o benchmark
            Vector VCopy(V.getCurrentSize());

            // * Copia o vetor original para o vetor auxiliar
            V.copy(VCopy);

            // * Ordena o vetor com o tamanho de partição t
            this->sort(VCopy, t, V.getCurrentSize() - 1);

            // * Define o tamanho de partição
            this->stats.setMPS(t);

            // * Calcula o custo do vetor ordenado
            this->stats.calculateCost(a, b, c);

            // * Armazena as stats na posição correspondente
            stats[numMPS] = this->stats;

            // * Printa as estatísticas do vetor ordenado
            stats[numMPS].print(); //! Isso vai para o benchmark

            // * Limpa as estatísticas
            this->stats.clear();

            // * Incrementa o número de tamanhos de partição
            numMPS++;

            //VCopy.print(); //

            VCopy.clear();
        }

        // * Calcula o menor custo entre os tamanhos de partição
        int minCostIdx = minCostIndex(stats, numMPS);

        // * Calcula o novo range de tamanhos de partição
        this->calculateNewRange(minCostIdx, minMPS, maxMPS, rangeMPS, numMPS);

        //* Calcula a diferença de custo entre os extremos
        diffCusto = stats[0].getCost() - stats[numMPS - 1].getCost();
        if (diffCusto < 0) {
            diffCusto = -diffCusto; // * Se o valor for negativo, transforma em positivo
        }

        // * Atualiza o melhor limiar de partição
        partitionThreshold = stats[minCostIdx].getMPS();

        iter++;

        // * Printa as estatísticas de cada iteração, numero de diferentes tamanhos de partição, limiar de partição e diferença de custo
        this->printIterStats(numMPS, partitionThreshold, diffCusto); // ! Isso vai para o benchmark

        std::cout << std::endl; // ! Isso vai para o benchmark
    } while ((diffCusto > costThreshold) && (numMPS >= 5));

    return partitionThreshold; // * Retorna o melhor limiar de partição
}

// ! SEED E LIMIAR DE CUSTO SÃO PARAMETROS DO BENCHMARK
// int determineBreaksThreshold(int seed, int costThreshold, int minPartitionSize) {}

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

int UniversalSorter::minCostIndex(Statistics stats[], int numMPS) {
    int minCostIndex = 0;
    for (int i = 1; i < numMPS; i++) {
        if (stats[i].getCost() < stats[minCostIndex].getCost()) {
            minCostIndex = i;
        }
    }
    return minCostIndex;
}

// int UniversalSorter::minCostIndex(Statistics stats[], float quickCosts[], int numMQS) {
//     int minIndex = 0;
//     float minDiff = std::fabs(insertCosts[0] - quickCosts[0]);

//     for (int i = 1; i < numMQS; i++) {
//         float diff = std::fabs(insertCosts[i] - quickCosts[i]);
//         if (diff < minDiff) {
//             minDiff = diff;
//             minIndex = i;
//         }
//     }

//     return minIndex;
// }

void UniversalSorter::printIterStats(int numMPS, int partitionThreshold, float MPSDiff) {
    std::cout << "nummps " << numMPS << " limParticao " << partitionThreshold << " mpsdiff " << MPSDiff << "\n";
}