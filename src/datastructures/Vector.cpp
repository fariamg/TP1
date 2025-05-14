#include "include/datastructures/Vector.h"

#include <iostream>
#include <stdexcept>

// Construtor com capacidade definida pelo usuário, limitada ao MAX_SIZE
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

// Retorna o elemento em uma posição válida ou lança exceção
int Vector::getElement(int index) const {
    if (index < 0 || index >= currentSize) {
        throw std::out_of_range("getElement: índice fora dos limites");
    }
    return data[index];
}

// Adiciona um valor ao final do vetor, se houver espaço
void Vector::push_back(int value) {
    if (currentSize >= capacity) {
        std::cerr << "Erro: vetor cheio. push_back falhou.\n";
        return;
    }
    data[currentSize++] = value;
}

// Retorna o tamanho atual do vetor
int Vector::getCurrentSize() const {
    return currentSize;
}

// Retorna se o vetor está vazio
bool Vector::isEmpty() const {
    return currentSize == 0;
}

// Limpa o vetor (reseta o tamanho)
void Vector::clear() {
    if (isEmpty()) {
        std::cerr << "Aviso: vetor já está vazio.\n";
        return;
    }
    currentSize = 0;
}

// Imprime todos os elementos armazenados
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

// Troca os valores entre dois índices válidos
void Vector::swap(int index1, int index2) {
    if (index1 < 0 || index1 >= currentSize || index2 < 0 || index2 >= currentSize) {
        throw std::out_of_range("swap: índice(s) fora dos limites");
    }
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}
