#pragma once

#include <iostream>
#include <string>

/// @ Cuida da coleta de estatísticas de execução do algoritmo
class Statistics {
  private:
    int comparisons;           //* Número de comparações
    int movements;             //* Número de movimentações
    int functionCalls;         //* Número de chamadas de função
    double cost;               // * Custo total
    int MPS;                   //* Tamanho de partição
    std::string algorithmName; //* Algoritmo utilizado

  public:
    static constexpr std::size_t ALGORITHM_NAME_SIZE = 2;

    //@ Construtor padrão explícito (evita conversões implícitas)
    Statistics();

    //@ Incrementa o número de comparações
    void incrementComparisons(int cmp) noexcept;

    //@ Incrementa o número de movimentações
    void incrementMovements(int moves) noexcept;

    //@ Incrementa o número de chamadas de função
    void incrementFunctionCalls(int calls) noexcept;

    //@ Retorna o número total de comparações
    int getComparisons() const noexcept;

    //@ Retorna o número total de movimentações
    int getMovements() const noexcept;

    //@ Retorna o número total de chamadas de função
    int getFunctionCalls() const noexcept;

    //@ Retorna o custo total
    double getCost() const noexcept;

    // @ Retorna o número de MPS
    int getMPS() const noexcept;

    //@ Define o número de MPS
    void setMPS(int mps) noexcept;

    void resetStats() noexcept;

    //@ Define o custo total
    void calculateCost(double a, double b, double c) noexcept;

    ///@ Retorna o nome do algoritmo
    const std::string& getAlgorithmName() const noexcept;

    //@ Define o nome do algoritmo
    void setAlgorithmName(const std::string& name) noexcept;

    //@ Printa na saída padrão as estatísticas
    void print() const noexcept;

    //@ Limpa as estatísticas
    void clear() noexcept;
};