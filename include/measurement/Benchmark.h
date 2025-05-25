#pragma once

#include "measurement/Statistics.h"
#include "measurement/Timer.h"
#include "datastructures/Vector.h"

//@ Cuida da execução do algoritmo, medindo o tempo e coletando estatísticas
class Benchmark {
  private:
    Timer timer;
    double a, b, c; // * Esses atributos são específicos do Benchmark, pois podem variar a cada execução
    int seed;
    double costThreshold;

  public:
    //@ Construtor que recebe os coeficientes e parametros do benchmark
    Benchmark(double a, double b, double c, int seed, double costThreshold);

    //@ Método que executa o benchmark em um vetor
    void run(Vector& V);
};