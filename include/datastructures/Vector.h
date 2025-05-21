#pragma once

#include <iterator>

static constexpr size_t MAX_SIZE = 10000;

//@ Estrutura de dados para armazenar tipo inteiro
class Vector {
  private:
    int data[MAX_SIZE];
    int currentSize;
    int capacity;

  public:
    //@ Construtor com capacidade definida pelo usuário, limitada ao MAX_SIZE
    Vector(int capacity) noexcept;

    //@ Retorna o elemento em uma posição válida ou lança exceção
    int getElement(int index) const;

    //@ Retorna o tamanho atual do vetor
    int getCurrentSize() const noexcept;

    //@ Retorna quantas vezes o numéro é menor que seu antecessor imediato (mede a desordem)
    int getNumBreaks() const noexcept;

    //@ Altera um elemento
    void setElement(int index, int value);

    //@ Adiciona um valor ao final do vetor, se houver espaço
    void push_back(int value) noexcept;

    // @ Preenche todo o vetor com numeros ordenados
    void fill() noexcept;

    //@ Retorna se o vetor está vazio
    bool isEmpty() const noexcept;

    //@ Limpa o vetor (reseta o tamanho)
    void clear() noexcept;

    //@ Retorna o tamanho máximo do vetor
    void print() const noexcept;

    //@ Troca os valores entre dois índices válidos
    void swap(int index1, int index2);

    //@ Copia o vetor atual para outro vetor
    void copy(Vector& other) noexcept;

    //@ Embaralha o vetor, de acordo com o número de quebras
    void shuffle(int numBreaks) noexcept;
};