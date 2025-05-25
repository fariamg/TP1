#include <algorithm>
#include <cmath>

#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "core/CalibrationCacheManager.h"
#include "core/UniversalSorter.h"
#include "measurement/Statistics.h"
#include <iomanip>

void UniversalSorter::sort(Vector& V_op, int minPartitionSize, int breakThreshold, Statistics& stats) {
    int vectorSize = V_op.getCurrentSize();
    int vectorBreaks = V_op.getNumBreaks();
    stats.resetStats(); //* Garante que as estatísticas estão limpas para esta operação

    if (vectorBreaks < breakThreshold) {
        insertionSort(V_op, 0, vectorSize - 1, stats);
    } else {
        if (vectorSize > minPartitionSize && vectorSize > 0) {
            quickSort(V_op, minPartitionSize, 0, vectorSize - 1, stats);
        } else if (vectorSize > 0) { //* Se não for grande o suficiente para QS ou minPartitionSize for grande
            insertionSort(V_op, 0, vectorSize - 1, stats);
        }
    }
}

void UniversalSorter::adaptiveSort(Vector& V_to_sort, int seed, double costThreshold, double a, double b, double c, Statistics& finalSortStats) {
    CalibrationCacheManager::initialize();

    int currentSize = V_to_sort.getCurrentSize();
    if (currentSize == 0) {
        finalSortStats.resetStats();
        finalSortStats.setAlgorithmName("none");
        //* O custo será 0 por padrão se resetStats() zerar tudo, incluindo o custo.
        //* Se calculateCost for chamado, ele confirmará 0.
        finalSortStats.calculateCost(a, b, c); //* Calcula o custo (será 0 para vetor vazio)
        std::cout << "INFO: Vetor está vazio. Nada a ordenar." << std::endl;
    } else {
        int minPartitionSize_calibrated;
        int breaksThreshold_calibrated;

        //* Passar a, b, c para getThresholds
        std::optional<std::pair<int, int>> cachedThresholds = CalibrationCacheManager::getThresholds(currentSize, a, b, c);

        if (cachedThresholds.has_value()) {
            minPartitionSize_calibrated = cachedThresholds.value().first; //* Obtém o tamanho mínimo de partição do cache
            breaksThreshold_calibrated = cachedThresholds.value().second; //* Obtém o limiar de quebras do cache
            std::cout << "INFO: Usando calibração do cache para tamanho " << currentSize << " (parametros: a=" << a << ",b=" << b << ",c=" << c << ")"
                      << ": MPS=" << minPartitionSize_calibrated << ", LQ_threshold=" << breaksThreshold_calibrated << std::endl;
        } else {
            std::cout << "INFO: Calibrando para tamanho " << currentSize << " (parametros: a=" << a << ",b=" << b << ",c=" << c << ")" << "..."
                      << std::endl;

            Vector V_copy_for_mps_calib(currentSize); // * Cria um vetor auxiliar para calibração de MPS
            V_to_sort.copy(V_copy_for_mps_calib);
            minPartitionSize_calibrated = determinePartitionThreshold(V_copy_for_mps_calib, costThreshold, a, b, c);

            Vector V_copy_for_lq_calib(currentSize); // * Cria um vetor auxiliar para calibração de LQ
            V_to_sort.copy(V_copy_for_lq_calib);
            Statistics tempSortStats;
            quickSort(V_copy_for_lq_calib, minPartitionSize_calibrated, 0, V_copy_for_lq_calib.getCurrentSize() - 1, tempSortStats);
            breaksThreshold_calibrated = determineBreaksThreshold(V_copy_for_lq_calib, seed, costThreshold, minPartitionSize_calibrated, a, b, c);

            //* Passar a, b, c para storeThresholds
            CalibrationCacheManager::storeThresholds(currentSize, a, b, c, minPartitionSize_calibrated, breaksThreshold_calibrated);
            std::cout << "INFO: Calibração completa para tamanho " << currentSize << ". Armazenado: MPS=" << minPartitionSize_calibrated
                      << ", LQ_threshold=" << breaksThreshold_calibrated << std::endl;
        }

        std::cout << "INFO: Ordenando vetor original com limiares calibrados..." << std::endl;
        //* finalSortStats é passado por referência e será preenchido por sort() com CMP, MOV, CALLS
        this->sort(V_to_sort, minPartitionSize_calibrated, breaksThreshold_calibrated, finalSortStats);

        //* Calcula o custo total da ordenação final
        finalSortStats.calculateCost(a, b, c);
    }

    //* Imprime estatísticas da ordenação final
    std::cout << "INFO: Ordenação adaptativa final completa. Algoritmo: " << finalSortStats.getAlgorithmName()
              << ", CMP: " << finalSortStats.getComparisons() << ", MOV: " << finalSortStats.getMovements()
              << ", CALLS: " << finalSortStats.getFunctionCalls() << ", Custo: ";
    if (finalSortStats.getCost() != 0.0 ||
        (finalSortStats.getComparisons() == 0 && finalSortStats.getMovements() == 0 && finalSortStats.getFunctionCalls() == 0 && currentSize == 0)) {
        std::cout << std::fixed << std::setprecision(9) << finalSortStats.getCost();
    } else if (finalSortStats.getComparisons() != 0 || finalSortStats.getMovements() != 0 || finalSortStats.getFunctionCalls() != 0) {
        std::cout << std::fixed << std::setprecision(9) << finalSortStats.getCost();
    } else {
        std::cout << "0.000000000"; //* Para o caso de vetor vazio onde tudo é 0
    }
    std::cout << std::endl;
}

// !  Os parametros são atributos do benchmark (cada benchmark pode receber valores diferentes)
int UniversalSorter::determinePartitionThreshold(Vector& V_calibrate_on, double costThreshold, double a, double b, double c) {
    int minMPS = 2; // * Tamanhos 0 e 1 já estão ordenados

    int maxMPS = V_calibrate_on.getCurrentSize(); // * Tamanho de partição até o tamanho maximo do vetor

    int rangeMPS = (maxMPS - minMPS) / 5; // * Se V size for 100, testaremos, por exemplo: 2, 22, 42, 62, 82 e 100 ((100-2)/5 = 98/5 = 19.6 ≈ 20)
    if (rangeMPS == 0)
        rangeMPS = 1;

    int numMPS = 5;

    int partitionThreshold = 0; // * Inicializa o melhor limiar de partição

    float diffCusto = costThreshold + 1; // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição

    int iter = 0; // * Contador de iterações

    Statistics stats[10]; // * Array para armazenar as stats de cada iteração

    while ((diffCusto > costThreshold) && (numMPS >= 5)) {
        std::cout << "iter " << iter << "\n";

        // * Zera o número do tamanho da partição
        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += rangeMPS) {
            // * Cria-se um vetor do tamanho do vetor original (desalocado após sair do escopo)
            Vector VCopy(V_calibrate_on.getCurrentSize());

            // * Copia o vetor original para o vetor auxiliar
            V_calibrate_on.copy(VCopy);

            stats[numMPS].resetStats(); // * Reseta as estatísticas

            // * Ordena o vetor com o tamanho de partição t
            this->sort(VCopy, t, 1, stats[numMPS]);

            // * Define o tamanho de partição
            stats[numMPS].setMPS(t);

            // * Calcula o custo do vetor ordenado
            stats[numMPS].calculateCost(a, b, c);

            // * Printa as estatísticas do vetor ordenado
            stats[numMPS].print();

            // * Incrementa o número de tamanhos de partição
            numMPS++;

            VCopy.clear();
        }
        // * Calcula o menor custo entre os tamanhos de partição
        partitionThreshold = minCostIndex(stats, numMPS);

        int newMin = 0, newMax = 0;

        // * Calcula o novo range de tamanhos de partição
        this->calculateNewRange(partitionThreshold, stats, minMPS, maxMPS, rangeMPS, newMax, newMin, numMPS);

        //* Calcula a diferença de custo entre os extremos
        diffCusto = fabs(stats[newMin].getCost() - stats[newMax].getCost());

        iter++;

        // * Printa as estatísticas de cada iteração, numero de diferentes tamanhos de partição, limiar de partição e diferença de custo
        this->printIterStats(numMPS, stats[partitionThreshold].getMPS(), diffCusto);

        std::cout << std::endl;
    }
    return stats[partitionThreshold].getMPS(); // * Retorna o melhor limiar de partição
}

int UniversalSorter::determineBreaksThreshold(Vector& V_sorted_calibrate_on, int seed, double costThreshold, int minPartitionSize, double a, double b,
                                              double c) {
    int minMBS = 1;                                          // * Tamanhos 0 e 1 já estão ordenados
    int maxMBS = V_sorted_calibrate_on.getCurrentSize() / 2; // * Tamanho de partição até o tamanho maximo do vetor
    int rangeMBS = (maxMBS - minMBS) / 5;
    int numMBS = 5; // * Número de quebras

    if (rangeMBS == 0)
        rangeMBS = 1;

    float diffCusto = costThreshold + 1; // * Diff Custo é a diferença de custo entre os extremos dos valores de tamanho de partição
    int breaksThreshold = 0;             // * Inicializa o melhor limiar de quebras

    Statistics QSstats[10], ISstats[10]; // * Array para armazenar as stats dos algoritmos de cada iteração

    int iter = 0; // * Contador de iterações

    while ((diffCusto > costThreshold) && (numMBS >= 5)) {
        std::cout << "iter " << iter << "\n";

        numMBS = 0;

        for (int t = minMBS; t <= maxMBS; t += rangeMBS) {
            Statistics stats;
            quickSort(V_sorted_calibrate_on, -1, 0, V_sorted_calibrate_on.getCurrentSize() - 1, stats);

            //* Cria um vetor auxiliar para armazenar o vetor ordenado
            Vector baseSortedVector(V_sorted_calibrate_on.getCurrentSize());
            V_sorted_calibrate_on.copy(baseSortedVector);

            //* Cria cópias do vetor ordenado para os algoritmos de ordenação
            Vector VCopy1(V_sorted_calibrate_on.getCurrentSize()), VCopy2(V_sorted_calibrate_on.getCurrentSize());
            baseSortedVector.copy(VCopy1);
            baseSortedVector.copy(VCopy2);

            Statistics qsStats, isStats;
            qsStats.resetStats();
            isStats.resetStats();

            srand48(seed);
            VCopy1.shuffle(t);

            srand48(seed);
            VCopy2.shuffle(t);

            //* QuickSort com estatísticas limpas
            quickSort(VCopy1, minPartitionSize, 0, VCopy1.getCurrentSize() - 1, qsStats);
            qsStats.setMPS(t);
            qsStats.calculateCost(a, b, c);

            //* InsertionSort com estatísticas limpas
            insertionSort(VCopy2, 0, VCopy2.getCurrentSize() - 1, isStats);
            isStats.setMPS(t);
            isStats.calculateCost(a, b, c);

            //* Atualiza os arrays de estatísticas
            QSstats[numMBS] = qsStats;
            ISstats[numMBS] = isStats;

            std::cout << "qs lq " << t << " cost " << std::fixed << std::setprecision(9) << qsStats.getCost() << " cmp " << qsStats.getComparisons()
                      << " move " << qsStats.getMovements() << " calls " << qsStats.getFunctionCalls() << "\n";

            std::cout << "in lq " << t << " cost " << std::fixed << std::setprecision(9) << isStats.getCost() << " cmp " << isStats.getComparisons()
                      << " move " << isStats.getMovements() << " calls " << isStats.getFunctionCalls() << "\n";

            numMBS++;
        }
        // * Calcula o menor custo entre os tamanhos de partição
        breaksThreshold = minCostIndex(ISstats, QSstats, numMBS);

        int newMin = 0, newMax = 0;

        // * Calcula o novo range de tamanhos de partição
        this->calculateNewRange(breaksThreshold, ISstats, minMBS, maxMBS, rangeMBS, newMin, newMax, numMBS);

        //* Calcula a diferença de custo entre os extremos
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
    int minIdx = 0;
    for (int i = 1; i < numMBS; i++) {
        double curr = std::fabs(stats1[i].getCost() - stats2[i].getCost());
        double best = std::fabs(stats1[minIdx].getCost() - stats2[minIdx].getCost());
        if (curr < best) {
            minIdx = i;
        }
    }
    return minIdx;
}

void UniversalSorter::printIterStats(int numMPS, int partitionMPS, double MPSDiff) {
    std::cout << std::fixed << std::setprecision(6) << "nummps " << numMPS << " limParticao " << partitionMPS << " mpsdiff " << MPSDiff << "\n";
}
