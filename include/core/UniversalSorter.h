#pragma once

#include "datastructures/Vector.h"
#include "measurement/Statistics.h"

class UniversalSorter {
  private:
    Statistics stats;

  public:
    Vector V; // ?Esse vector não pode estar aqui, preciso passar um  vector pronto para o sorter, ppois para o mesmo vector posso fazer diferentes
              // benchmarks
    //@ Construtor padrão
    UniversalSorter(Vector& V);

    Statistics getStats() const noexcept;

    //@ Método para ordenar o vetor
    void sort(int minPartitionSize, int breakLimit);

    //@ Método para determinar o limite de partição para o QuickSort ser mais eficiente
    int determinePartitionThreshold(int costThreshold, double a, double b, double c);

    //@ Define o limite de quebras para o InsertionSort ser mais eficiente
    void determineBreaksThreshold(int costThreshold, int minPartitionSize);

    //@ Método para calcular o novo intervalo
    void calculateNewRange(int partitionThreshold, int& minMPS, int& maxMPS, int& rangeMPS, int numMPS);

    // @ Metodo que calcula o menor custo
    int minCostIndex(float costs[], int numMPS);

    //@ Método para imprimir as estatísticas de cada iteração
    void printIterStats(int numMPS, int partitionThreshold, float MPSDiff);
};
