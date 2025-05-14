#pragma once

#include <iostream>
#include <string>

class Statistics {
  public:
    explicit Statistics(const std::string& algorithmName);

    // Incrementa o número de comparações
    void incrementComparisons() noexcept;

    // Incrementa o número de movimentações
    void incrementMovements() noexcept;

    // Incrementa o número de chamadas de função
    void incrementFunctionCalls() noexcept;

    // Retorna o número total de comparações
    int getComparisons() const noexcept;

    // Retorna o número total de movimentações
    int getMovements() const noexcept;

    // Retorna o número total de chamadas de função
    int getFunctionCalls() const noexcept;

    // Retorna o nome do algoritmo
    const std::string& getAlgorithmName() const noexcept;

  private:
    int comparisons;   // Número de comparações
    int movements;     // Número de movimentações
    int functionCalls; // Número de chamadas de função
    std::string algorithmName; // Algoritmo utilizado
};