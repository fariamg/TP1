#pragma once

#include <chrono>

class Timer {
  private:
    Clock::time_point startTime;
    Clock::time_point endTime;
    
  public:
    using Clock = std::chrono::steady_clock;

    Timer() noexcept;

    void start() noexcept;
    void stop() noexcept;

    // Retorna o tempo decorrido em segundos
    double elapsedSeconds() const noexcept;

    // Retorna o tempo decorrido em milissegundos
    long Nananoseconds() const noexcept; // TODO: pode ser que long não seja o melhor tipo
};
