#pragma once

#include "measurement/Statistics.h"
#include "datastructures/Vector.h"
#include "measurement/Timer.h"
//? Quem vai cuidar da escrita das estatisticas: benchmark ou algoritmo?
//@ Cuida da execução do algoritmo, medindo o tempo e coletando estatísticas
class Benchmark {
  private:
    Timer timer;
    Statistics stats;

  public:
  //@ Construtor recebe o nome do algoritmo e a capacidade do vetor
  //? Talvez vou tirar o nome do algoritmo de parametro do construtor das stats (pois o nome do algoritmo é o mesmo do benchmark)
    Benchmark(Vector V) : stats() {} // TODO: de alguma forma precisa ligar ao algoritmo

    void run(); // ? Como vai fazer isso (na chamada da funçao livre do algoritmo precisa passar Statistics por referência)
};