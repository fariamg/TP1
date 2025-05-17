#pragma once

#include <iostream>
#include <string>

/// @ Cuida da coleta de estatísticas de execução do algoritmo
class Statistics {
  private:
    int comparisons;           //* Número de comparações
    int movements;             //* Número de movimentações
    int functionCalls;         //* Número de chamadas de função
    //std::string algorithmName; //* Algoritmo utilizado

  public:
    //static constexpr std::size_t ALGORITHM_NAME_SIZE = 2;

    //@ Construtor padrão explícito (evita conversões implícitas)
    explicit Statistics();

    //@ Incrementa o número de comparações
    void incrementComparisons(int cmp) noexcept;

    //@ Incrementa o número de movimentações
    void incrementMovements(int mvs) noexcept;

    //@ Incrementa o número de chamadas de função
    void incrementFunctionCalls(int cll) noexcept;

    //@ Retorna o número total de comparações
    int getComparisons() const noexcept;

    //@ Retorna o número total de movimentações
    int getMovements() const noexcept;

    //@ Retorna o número total de chamadas de função
    int getFunctionCalls() const noexcept;

    //@ Retorna o nome do algoritmo
    const std::string& getAlgorithmName() const noexcept;
};