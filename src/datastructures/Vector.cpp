#include "datastructures/Vector.h"

#include <iostream>
#include <stdexcept>

/*
 * Implementado um vetor estático (array de tamanho fixo) para eliminar a sobrecarga
 * de alocações e desalocações dinâmicas em tempo de execução, aumentando a performance.
 * A capacidade máxima precisa ser definida antecipadamente, o que pode gerar
 * desperdício de espaço, mas garante acesso mais rápido e previsível aos elementos.
 * Essa abordagem é adequada quando o gerenciamento de memória não é crítico
 * e o desempenho de acesso se torna prioridade, contexto em que se encontra a situação problema do TP.
 */
Vector::Vector(int capacity) noexcept : currentSize(0) {
    if (capacity > static_cast<int>(MAX_SIZE)) {
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

int Vector::getCurrentSize() const noexcept {
    return currentSize;
}

int Vector::getNumBreaks() const noexcept {
    int breaks = 0;
    for (int i = 0; i < currentSize - 1; ++i) {
        if (data[i] > data[i + 1]) {
            ++breaks;
        }
    }
    return breaks;
}

void Vector::setElement(int index, int value) {
    if (index < 0 || index >= currentSize) {
        throw std::out_of_range("setElement: índice fora dos limites");
    }
    data[index] = value;
}

void Vector::push_back(int value) noexcept {
    if (currentSize >= capacity) {
        std::cerr << "Erro: vetor cheio. push_back falhou.\n";
        return;
    }
    data[currentSize] = value;
    this->currentSize++;
}

void Vector::fill() noexcept {
    for (int i = 0; i < this->currentSize; ++i) {
        this->push_back(i);
    }
}

bool Vector::isEmpty() const noexcept {
    return currentSize == 0;
}

void Vector::clear() noexcept {
    if (isEmpty()) {
        std::cerr << "Aviso: vetor já está vazio.\n";
        return;
    }
    currentSize = 0;
}

void Vector::print() const noexcept {
    if (isEmpty()) {
        std::cout << "[empty]\n";
        return;
    }
    for (int i = 0; i < currentSize; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

void Vector::swap(int index1, int index2) {
    if (index1 < 0 || index1 >= currentSize || index2 < 0 || index2 >= currentSize) {
        throw std::out_of_range("swap: índice(s) fora dos limites");
    }
    int temp = data[index1];
    data[index1] = data[index2];
    data[index2] = temp;
}

void Vector::copy(Vector& other) noexcept {
    if (this == &other) {
        std::cerr << "Aviso: cópia de si mesmo. Nenhuma ação realizada.\n";
        return;
    }
    if (other.capacity < this->currentSize) {
        std::cerr << "Erro: capacidade insuficiente no vetor de destino. Cópia não realizada.\n";
        return;
    }
    other.currentSize = this->currentSize;
    for (int i = 0; i < currentSize; ++i) {
        other.data[i] = this->data[i]; 
    }
}
int Vector::shuffle(int numShuffle) {
    int currentSize = this->currentSize;
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++) {
        while (p1 == p2) {
            p1 = (int)(drand48() * currentSize);
            p2 = (int)(drand48() * currentSize);
        }
        temp = this->getElement(p1);
        this->setElement(p1, this->getElement(p2));
        this->setElement(p2, temp);
        p1 = p2 = 0;
    }
    return 0;
}