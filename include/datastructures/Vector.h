#pragma once

#include <iterator>

static constexpr size_t MAX_SIZE = 500;

class Vector {
  private:
    int data[MAX_SIZE];
    int currentSize = 0;
    int capacity;

  public:
    //@ Construtor com capacidade definida pelo usuário, limitada ao MAX_SIZE
    Vector(int capacity) noexcept;

    //@ Retorna o elemento em uma posição válida ou lança exceção
    int getElement(int index) const;
    
    //@ Retorna o tamanho atual do vetor
    int getCurrentSize() const noexcept;

    ////void setElement(int index, int value);

    //@ Adiciona um valor ao final do vetor, se houver espaço
    void push_back(int value);

    ////void pop_back();

    //@ Retorna se o vetor está vazio
    bool isEmpty() const noexcept;

    //@ Limpa o vetor (reseta o tamanho)
    void clear();

    //@ Retorna o tamanho máximo do vetor
    void print() const noexcept;

    //@ Troca os valores entre dois índices válidos
    void swap(int index1, int index2);
};