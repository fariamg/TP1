#pragma once

#include <iterator>

// Utilizando vetor estático devido a lentidão de alocação dinâmica
// A utilização de alocação antecipada é mais rápida, mas o tamanho máximo do vetor deve ser definido
// Pode ser que haja desperdício de memória, mas o tempo de execução é menor 
static constexpr size_t MAX_SIZE = 500; 

class Vector {
  private:
    int data[MAX_SIZE];
    int currentSize = 0;
    int capacity;

  public:
    Vector(int capacity) noexcept;

    int getElement(int index) const;
    int getCurrentSize() const noexcept;

    //void setElement(int index, int value);

    void push_back(int value);
    //void pop_back();
    bool isEmpty() const noexcept;
    void clear();
    void print() const noexcept;
    void swap(int index1, int index2);
};