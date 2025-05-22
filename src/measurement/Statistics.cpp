#include "measurement/Statistics.h"
#include <string>

Statistics::Statistics() : comparisons(0), movements(0), functionCalls(0) {}

void Statistics::incrementComparisons(int cmp) noexcept {
    this->comparisons += cmp;
}

void Statistics::incrementMovements(int moves) noexcept {
    this->movements += moves;
}

void Statistics::incrementFunctionCalls(int calls) noexcept {
    this->functionCalls += calls;
}

int Statistics::getComparisons() const noexcept {
    return this->comparisons;
}

int Statistics::getMovements() const noexcept {
    return this->movements;
}

int Statistics::getFunctionCalls() const noexcept {
    return this->functionCalls;
}

const std::string& Statistics::getAlgorithmName() const noexcept {
    return this->algorithmName;
}

double Statistics::getCost() const noexcept {
    return this->cost;
}

int Statistics::getMPS() const noexcept {
    return this->MPS;
}

void Statistics::setMPS(int mps) noexcept {
    this->MPS = mps;
}

void Statistics::calculateCost(int a, int b, int c) noexcept {
    this->cost = (a * this->comparisons + b * this->movements + c * this->functionCalls);
}

void Statistics::print() const noexcept {
    std::cout << this->getAlgorithmName() << " mps " << this->MPS << " cost " << this->cost << " cmp " << this->comparisons << " move "
              << this->movements << " calls " << this->functionCalls << std::endl;
}

void Statistics::clear() noexcept {
    this->comparisons = 0;
    this->movements = 0;
    this->functionCalls = 0;
}

void Statistics::setAlgorithmName(const std::string& name) noexcept {
    if (name.size() > ALGORITHM_NAME_SIZE) {
        std::cerr << "Error: Algorithm name exceeds maximum size." << std::endl;
        return;
    }
    this->algorithmName = name;
}