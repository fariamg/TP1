#include <algorithm>
#include <cmath>

#include "InsertionSort.h"
#include "QuickSort.h"
#include "Statistics.h"
#include "UniversalSorter.h"

UniversalSorter::UniversalSorter(Vector& V) : V(V) {}

// Statistics UniversalSorter::getStats() const noexcept {
//      return this->stats;
//  }

void UniversalSorter::sort(Vector& V, int minPartitionSize, int breakLimit, Statistics& stats) {
    int vectorSize = V.getCurrentSize();
    int vectorBreaks = V.getNumBreaks();

    if (vectorBreaks < breakLimit) {
        //* Vetor "quase ordenado" utiliza InsertionSort
        insertionSort(V, 0, vectorSize - 1, stats);
    } else {
        if (vectorSize > minPartitionSize) {
            //* Já se tiver muitas quebras e o tamanho do vetor for maior que o tamanho mínimo de partição usa QuickSort
            quickSort(V, minPartitionSize, 0, vectorSize - 1, stats);
        } else {
            // * Já se for menor ou igual utiliza InsertionSort (em vetores pequenos, a sobrecarga do quicksort não compensa)
            insertionSort(V, 0, vectorSize - 1, stats);
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

    int partitionThreshold; // * Inicializa o melhor limiar de partição
    int diffCusto;          // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição
    Statistics stats[6];    // * Array para armazenar as stats de cada iteração
    int iter = 0;           // * Contador de iterações

    // ! Coloquei esse do-while para não precisar inicializar o diffCusto com um valor arbitrariamente grande
    do {
        std::cout << "iter " << iter << "\n"; // ! Isso vai para o benchmark

        // * Zera o número do tamanho da partição
        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += rangeMPS) {
            // * Cria-se um vetor do tamanho do vetor original (desalocado após sair do escopo)
            Vector VCopy(V.getCurrentSize());

            // * Copia o vetor original para o vetor auxiliar
            V.copy(VCopy);

            // * Ordena o vetor com o tamanho de partição t
            this->sort(VCopy, t, V.getCurrentSize() - 1, stats[numMPS]);

            // * Define o tamanho de partição
            stats[t].setMPS(t);

            // * Calcula o custo do vetor ordenado
            stats[t].calculateCost(a, b, c);

            // // * Armazena as stats na posição correspondente
            // stats[numMPS] = this->stats;

            // * Printa as estatísticas do vetor ordenado
            stats[numMPS].print(); //! Isso vai para o benchmark

            // * Limpa as estatísticas
            // this->stats.clear();

            // * Incrementa o número de tamanhos de partição
            numMPS++;

            // VCopy.print(); //

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
int UniversalSorter::determineBreaksThreshold(int seed, int costThreshold, int minPartitionSize, int a, int b, int c) {
    int minMBS = 2;                      // * Tamanhos 0 e 1 já estão ordenados
    int maxMBS = V.getCurrentSize() / 2; // * Tamanho de partição até o tamanho maximo do vetor
    int rangeMBS = (int)(maxMBS - minMBS) / 5;
    int numMBS; // * Número de quebras

    if (rangeMBS == 0)
        rangeMBS = 1;

    int diffCusto;       // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição
    int breaksThreshold; // * Inicializa o melhor limiar de quebras

    Statistics QSstats[6]; // * Array para armazenar as stats do QuickSort de cada iteração
    Statistics ISstats[6]; // * Array para armazenar as stats do InsertionSort de cada iteração

    int iter = 0; // * Contador de iterações

    do {
        std::cout << "iter " << iter << "\n";

        numMBS = 0;

        for (int t = minMBS; t <= maxMBS; t += rangeMBS) {
            Vector VCopy1(V.getCurrentSize());
            V.copy(VCopy1);

            Vector VCopy2(V.getCurrentSize());
            V.copy(VCopy2);

            VCopy1.shuffle(t); // * Embaralha o vetor original
            VCopy2.shuffle(t); // * Embaralha o vetor original

            quickSort(VCopy1, minPartitionSize, 0, V.getCurrentSize() - 1, QSstats[numMBS]);
            insertionSort(VCopy2, 0, V.getCurrentSize() - 1, ISstats[numMBS]);

            QSstats[numMBS].setMPS(t);
            ISstats[numMBS].setMPS(t);

            QSstats[numMBS].calculateCost(a, b, c);
            ISstats[numMBS].calculateCost(a, b, c);

            QSstats[numMBS].print(); // ! Isso vai para o benchmark
            ISstats[numMBS].print(); // ! Isso vai para o benchmark

            numMBS++;

            VCopy1.clear();
            VCopy2.clear();
        }

        int minCostIdx = minCostIndex(ISstats, QSstats, numMBS);

        this->calculateNewRange(minCostIdx, minMBS, maxMBS, rangeMBS, numMBS);

        diffCusto = ISstats[0].getCost() - ISstats[numMBS - 1].getCost();
        if (diffCusto < 0) {
            diffCusto = -diffCusto; // * Se o valor for negativo, transforma em positivo
        }

        breaksThreshold = ISstats[minCostIdx].getMPS();

        iter++;

        this->printIterStats(numMBS, breaksThreshold, diffCusto); // ! Isso vai para o benchmark

        std::cout << std::endl; // ! Isso vai para o benchmark
    } while ((diffCusto > costThreshold) && (numMBS >= 5));
    return breaksThreshold; // * Retorna o melhor limiar de quebras
}

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

int UniversalSorter::minCostIndex(Statistics stats1[], Statistics stats2[], int numMBS) {
    int minCostIndex = 0;
    for (int i = 1; i < V.getCurrentSize(); i++) {
        if (fabs(stats1[i].getCost() - stats2[i].getCost()) < fabs(stats1[minCostIndex].getCost() - stats2[minCostIndex].getCost())) {
            minCostIndex = i;
        }
    }
    return minCostIndex;
}

void UniversalSorter::printIterStats(int numMPS, int partitionThreshold, double MPSDiff) {
    std::cout << "nummps " << numMPS << " limParticao " << partitionThreshold << " mpsdiff " << MPSDiff << "\n";
}