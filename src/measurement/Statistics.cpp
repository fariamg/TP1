#include "measurement/Statistics.h"
#include <string>

Statistics::Statistics() : comparisons(0), movements(0), functionCalls(0) {}

void Statistics::incrementComparisons(int cmp) noexcept {
    comparisons += cmp;
}

void Statistics::incrementMovements(int moves) noexcept {
    movements += moves;
}

void Statistics::incrementFunctionCalls(int calls) noexcept {
    functionCalls += calls;
}

int Statistics::getComparisons() const noexcept {
    return comparisons;
}

int Statistics::getMovements() const noexcept {
    return movements;
}

int Statistics::getFunctionCalls() const noexcept {
    return functionCalls;
}

void Statistics::print() const noexcept {
    std::cout << "cmp" << this->comparisons << " move" << this->movements << " calls" << this->functionCalls << std::endl;
}

// const std::string& Statistics::getAlgorithmName() const noexcept {
//     return algorithmName;
// }
