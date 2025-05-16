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
    Vector data;

  public:
  //@ Construtor recebe o nome do algoritmo e a capacidade do vetor
    Benchmark(const std::string& algorithmName, int capacity) : stats(algorithmName), data(capacity) {} // TODO: de alguma forma precisa ligar ao algoritmo
    
    void run() // ? Como vai fazer isso (na chamada da funçao livre do algoritmo precisa passar Statistics por referência)
    {
        timer.start();
};