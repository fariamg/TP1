#pragma once

#include "Statistics.h"
#include "Vector.h"

class UniversalSorter {
  public:
    Vector V; // ?Esse vector não pode estar aqui, preciso passar um  vector pronto para o sorter, ppois para o mesmo vector posso fazer diferentes
              // benchmarks
    //@ Construtor padrão
    UniversalSorter(Vector& V);

    // Statistics getStats() const noexcept;

    //@ Método para ordenar o vetor
    void sort(Vector& V, int minPartitionSize, int breakThreshold, Statistics& stats);

    //@ Método para determinar o limite de partição para o QuickSort ser mais eficiente
    int determinePartitionThreshold(double costThreshold, double a, double b, double c);

    //@ Define o limite de quebras para o InsertionSort ser mais eficiente
    int determineBreaksThreshold(int seed, double costThreshold, int minPartitionSize, double a, double b, double c);

    //@ Método para calcular o novo intervalo
    void calculateNewRange(int minCostIdx, Statistics stats[], int& minMPS, int& maxMPS, int& rangeMPS, int& newMax, int& newMin,int numMPS);

    int minCostIndex(Statistics stats[], int numMPS);

    int minCostIndex(Statistics stats1[], Statistics stats2[], int numMBS);

    //@ Método para imprimir as estatísticas de cada iteração
    void printIterStats(int numMPS, int partitionThreshold, double MPSDiff);
};
