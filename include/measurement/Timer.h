#pragma once

#include <chrono>

//@ Cuida da medição de tempo de execução do algoritmo
class Timer {
  private:
    //* Usando o tipo de relógio steady_clock para medir o tempo
    using Clock = std::chrono::steady_clock;
    
    Clock::time_point startTime;
    Clock::time_point endTime;

  public:
    //@ Construtor padrão que não lança exceção
    Timer() noexcept;

    //@ Seta o tempo inicial
    void start() noexcept;

    //@ Seta o tempo final
    void stop() noexcept;

    //@ Retorna o tempo decorrido em segundos
    double elapsedSeconds() const noexcept;

    //@ Retorna o tempo decorrido em milissegundos
    long Nananoseconds() const noexcept; // TODO: pode ser que long não seja o melhor tipo
};
