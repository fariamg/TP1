#include <algorithm>
#include <cmath>

#include "InsertionSort.h"
#include "QuickSort.h"
#include "Statistics.h"
#include "UniversalSorter.h"
#include <iomanip>

UniversalSorter::UniversalSorter(Vector& V) : V(V) {}

void UniversalSorter::sort(Vector& V, int minPartitionSize, int breakThreshold, Statistics& stats) {
    int vectorSize = V.getCurrentSize();
    int vectorBreaks = V.getNumBreaks();

    if (vectorBreaks < breakThreshold) {
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
int UniversalSorter::determinePartitionThreshold(double costThreshold, double a, double b, double c) {
    int minMPS = 2; // * Tamanhos 0 e 1 já estão ordenados

    int maxMPS = V.getCurrentSize(); // * Tamanho de partição até o tamanho maximo do vetor

    int rangeMPS = (maxMPS - minMPS) / 5; // * Se V size for 100, testaremos, por exemplo: 2, 22, 42, 62, 82 e 100 ((100-2)/5 = 98/5 = 19.6 ≈ 20)
    if (rangeMPS == 0)
        rangeMPS = 1;

    int numMPS = 5;

    int partitionThreshold = 0; // * Inicializa o melhor limiar de partição

    float diffCusto = costThreshold + 1; // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição

    int iter = 0; // * Contador de iterações

    Statistics stats[10]; // * Array para armazenar as stats de cada iteração

    // int minCostIdx = 0;

    while ((diffCusto > costThreshold) && (numMPS >= 5)) {
        std::cout << "iter " << iter << "\n"; // ! Isso vai para o benchmark

        // * Zera o número do tamanho da partição
        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += rangeMPS) {
            // * Cria-se um vetor do tamanho do vetor original (desalocado após sair do escopo)
            Vector VCopy(V.getCurrentSize());

            // * Copia o vetor original para o vetor auxiliar
            V.copy(VCopy);

            stats[numMPS].resetStats(); // * Reseta as estatísticas

            // * Ordena o vetor com o tamanho de partição t
            this->sort(VCopy, t, 1, stats[numMPS]);

            // * Define o tamanho de partição
            stats[numMPS].setMPS(t);

            // * Calcula o custo do vetor ordenado
            stats[numMPS].calculateCost(a, b, c);

            // std::cout << "DEBUG - t=" << t << " cmp=" << stats[numMPS].getComparisons() << " mov=" << stats[numMPS].//getMovements()
            //<< " calls=" << stats[numMPS].getFunctionCalls() << " cost=" << stats[numMPS].getCost() << std::endl;

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
        int newMin = 0, newMax = 0;

        // * Calcula o menor custo entre os tamanhos de partição
        partitionThreshold = minCostIndex(stats, numMPS);

        // * Calcula o novo range de tamanhos de partição
        this->calculateNewRange(partitionThreshold, stats, minMPS, maxMPS, rangeMPS, newMax, newMin, numMPS);

        //* Calcula a diferença de custo entre os extremos
        diffCusto = fabs(stats[newMin].getCost() - stats[newMax].getCost());

        // * Atualiza o melhor limiar de partição
        // partitionThreshold = stats[partitionThreshold].getMPS();

        iter++;

        // * Printa as estatísticas de cada iteração, numero de diferentes tamanhos de partição, limiar de partição e diferença de custo
        this->printIterStats(numMPS, stats[partitionThreshold].getMPS(), diffCusto); // ! Isso vai para o benchmark

        std::cout << std::endl; // ! Isso vai para o benchmark
    }
    return stats[partitionThreshold].getMPS(); // * Retorna o melhor limiar de partição
}

// ! SEED E LIMIAR DE CUSTO SÃO PARAMETROS DO BENCHMARK
int UniversalSorter::determineBreaksThreshold(int seed, double costThreshold, int minPartitionSize, double a, double b, double c) {
    int minMBS = 1;                      // * Tamanhos 0 e 1 já estão ordenados
    int maxMBS = V.getCurrentSize() / 2; // * Tamanho de partição até o tamanho maximo do vetor
    int rangeMBS = (maxMBS - minMBS) / 5;
    int numMBS = 5; // * Número de quebras

    if (rangeMBS == 0)
        rangeMBS = 1;

    float diffCusto = costThreshold + 1; // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição
    int breaksThreshold = 0;             // * Inicializa o melhor limiar de quebras
    // int minCostIdx = 0;                  // * Inicializa o índice do menor custo

    Statistics QSstats[10], ISstats[10]; // * Array para armazenar as stats dos algoritmos de cada iteração

    int iter = 0; // * Contador de iterações
    while ((diffCusto > costThreshold) && (numMBS >= 5)) {
        std::cout << "iter " << iter << "\n";

        numMBS = 0;

        for (int t = minMBS; t <= maxMBS; t += rangeMBS) {
            Vector VCopy1(V.getCurrentSize()), VCopy2(V.getCurrentSize());
            V.copy(VCopy1);
            V.copy(VCopy2);

            Statistics qsStats, isStats; // Novas instâncias a cada iteração

            srand48(seed);
            VCopy1.shuffle(t);
            srand48(seed);
            VCopy2.shuffle(t);

            // QuickSort com estatísticas limpas
            quickSort(VCopy1, minPartitionSize, 0, V.getCurrentSize() - 1, qsStats);
            qsStats.setMPS(t);
            qsStats.calculateCost(a, b, c);

            // InsertionSort com estatísticas limpas
            insertionSort(VCopy2, 0, V.getCurrentSize() - 1, isStats);
            isStats.setMPS(t);
            isStats.calculateCost(a, b, c);

            // Atualiza os arrays de estatísticas
            QSstats[numMBS] = qsStats;
            ISstats[numMBS] = isStats;

            // Saída formatada
            std::cout << "qs lq " << t << " cost " << std::fixed << std::setprecision(9) << qsStats.getCost() << " cmp " << qsStats.getComparisons()
                      << " move " << qsStats.getMovements() << " calls " << qsStats.getFunctionCalls() << "\n";

            std::cout << "in lq " << t << " cost " << std::fixed << std::setprecision(9) << isStats.getCost() << " cmp " << isStats.getComparisons()
                      << " move " << isStats.getMovements() << " calls " << isStats.getFunctionCalls() << "\n";

            numMBS++;
        }
        int newMin = 0, newMax = 0;

        breaksThreshold = minCostIndex(ISstats, QSstats, numMBS);

        this->calculateNewRange(breaksThreshold, ISstats, minMBS, maxMBS, rangeMBS, newMin, newMax, numMBS);

        diffCusto = fabs(ISstats[newMax].getCost() - ISstats[newMin].getCost());

        std::cout << "numlq " << numMBS << " limQuebras " << ISstats[breaksThreshold].getMPS() << " lqdiff " << std::fixed << std::setprecision(6)
                  << diffCusto << "\n";
        if ((diffCusto > costThreshold) && (numMBS >= 5))
            std::cout << "\n";

        iter++;
    }
    return ISstats[breaksThreshold].getMPS();
}

void UniversalSorter::calculateNewRange(int minCostIdx, Statistics stats[], int& minMPS, int& maxMPS, int& rangeMPS, int& newMax, int& newMin,
                                        int numMPS) {
    if (minCostIdx == 0) {
        newMin = 0;
        newMax = 2;
    } else if (minCostIdx == numMPS - 1) {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    } else {
        newMin = minCostIdx - 1;
        newMax = minCostIdx + 1;
    }

    minMPS = stats[newMin].getMPS();
    maxMPS = stats[newMax].getMPS();
    rangeMPS = (int)(maxMPS - minMPS) / 5;

    // Medida de proteção para garantir que rangeMPS seja válido.
    if (rangeMPS == 0) {
        rangeMPS = 1;
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
    int min = 0;
    for (int i = 1; i < numMBS; i++) {
        double currentDiff = fabs(stats1[i].getCost() - stats2[i].getCost());
        double minDiff = fabs(stats1[min].getCost() - stats2[min].getCost());
        if (currentDiff < minDiff) {
            min = i;
        }
    }
    return min;
}

void UniversalSorter::printIterStats(int numMPS, int partitionMPS, double MPSDiff) {
    std::cout << std::fixed << std::setprecision(6) << "nummps " << numMPS << " limParticao " << partitionMPS << " mpsdiff " << MPSDiff << "\n";
}
