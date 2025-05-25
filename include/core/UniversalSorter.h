#pragma once

#include "measurement/Statistics.h"
#include "datastructures/Vector.h"

//@ Classe que implementa o algoritmo de ordenação adaptativa
class UniversalSorter {
  public:
    //@ Construtor padrão
    UniversalSorter() = default; 

    //@ Método principal de ordenação adaptativa
    void adaptiveSort(Vector& V_to_sort, int seed, double costThreshold, double a, double b, double c, Statistics& finalSortStats);

    //@ Método para ordenar o vetor com limiares já conhecidos
    void sort(Vector& V_op, int minPartitionSize, int breakThreshold, Statistics& stats); 

    //@ Método para determinar o limite de partição para o QuickSort ser mais eficiente
    int determinePartitionThreshold(Vector& V_calibrate_on, double costThreshold, double a, double b, double c);

    //@ Define o limite de quebras para o InsertionSort ser mais eficiente
    int determineBreaksThreshold(Vector& V_sorted_calibrate_on, int seed, double costThreshold, int minPartitionSize, double a, double b, double c);

    //@ Método para calcular o novo intervalo
    void calculateNewRange(int minCostIdx, Statistics stats[], int& minMPS, int& maxMPS, int& rangeMPS, int& newMax, int& newMin, int numMPS);

    //@ Metodo para determinar o índice do menor custo
    int minCostIndex(Statistics stats[], int numMPS);

    //@ Metodo para determinar o índice do menor custo
    int minCostIndex(Statistics stats1[], Statistics stats2[], int numMBS);

    //@ Método para imprimir as estatísticas de cada iteração
    void printIterStats(int numMPS, int partitionThreshold, double MPSDiff);
};