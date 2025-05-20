#pragma once

#include "datastructures/Vector.h"
#include "measurement/Statistics.h"
#include "measurement/Timer.h"

//@ Cuida da execução do algoritmo, medindo o tempo e coletando estatísticas
class Benchmark {
  private:
    Timer timer;
    //Statistics stats;
    // * Esses atributos são específicos do Benchmark, pois podem variar a cada execução
    double a, b, c; 
    int seed;
    int costThreshold;

  public:
    //@ Construtor que recebe o vetor e os coeficientes
    Benchmark(Vector& V, double a, double b, double c, int seed, int costThreshold){}

    void run() noexcept;
};