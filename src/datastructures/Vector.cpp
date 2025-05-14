#include "include/datastructures/Vector.h"

#include <iostream>
#include <stdexcept>

//* Utilizando vetor estático devido a lentidão de alocação dinâmica
//* A utilização de alocação antecipada é mais rápida, mas o tamanho máximo do vetor deve ser definido
//* Pode ser que haja desperdício de memória, mas o tempo de execução é menor
Vector::Vector(int capacity) {
    if (capacity > MAX_SIZE) {
        std::cerr << "Aviso: capacidade excede o máximo (" << MAX_SIZE << "). Será ajustada.\n";
        this->capacity = MAX_SIZE;
    } else if (capacity <= 0) {
        std::cerr << "Aviso: capacidade inválida. Será ajustada para 1.\n";
        this->capacity = 1;
    } else {
        this->capacity = capacity;
    }
}

int Vector::getElement(int index) const {
    if (index < 0 || index >= currentSize) {
        throw std::out_of_range("getElement: índice fora dos limites");
    }
    return data[index];
}

int Vector::getCurrentSize() const {
    return currentSize;
}

void Vector::setElement(int index, int value) {
    if (index < 0 || index >= currentSize) {
        throw std::out_of_range("setElement: índice fora dos limites");
    }
    data[index] = value;
}

void Vector::push_back(int value) {
    if (currentSize >= capacity) {
        std::cerr << "Erro: vetor cheio. push_back falhou.\n";
        return;
    }
    data[currentSize++] = value;
}

bool Vector::isEmpty() const {
    return currentSize == 0;
}

void Vector::clear() {
    if (isEmpty()) {
        std::cerr << "Aviso: vetor já está vazio.\n";
        return;
    }
    currentSize = 0;
}

void Vector::print() const {
    if (isEmpty()) {
        std::cout << "[empty]\n";
        return;
    }
    for (int i = 0; i < currentSize; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

/*void Vector::swap(int index1, int index2) {
    if (index1 < 0 || index1 >= currentSize || index2 < 0 || index2 >= currentSize) {
        throw std::out_of_range("swap: índice(s) fora dos limites");
    }
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}*/
