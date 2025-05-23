#pragma once

#include "Statistics.h"
#include "Timer.h"
#include "Vector.h"

//@ Cuida da execução do algoritmo, medindo o tempo e coletando estatísticas
class Benchmark {
  private:
    Timer timer;
    // * Esses atributos são específicos do Benchmark, pois podem variar a cada execução
    double a, b, c;
    int seed;
    int costThreshold;

  public:
    //@ Construtor que recebe os coeficientes e parametros do benchmark
    Benchmark(double a, double b, double c, int seed, int costThreshold);

    void run(Vector& V);
};