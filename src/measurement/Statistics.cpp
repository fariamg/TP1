#include <Statistics.h>
#include <string>

Statistics::Statistics(const std::string& algorithmName) : comparisons(0), movements(0), functionCalls(0) {
    if (algorithmName.size() > ALGORITHM_NAME_SIZE) {
        throw std::invalid_argument("Algorithm name exceeds maximum size");
    }
    this->algorithmName = algorithmName;
}

void Statistics::incrementComparisons() noexcept { ++comparisons; }

void Statistics::incrementMovements() noexcept { ++movements; }

void Statistics::incrementFunctionCalls() noexcept { ++functionCalls; }

int Statistics::getComparisons() const noexcept { return comparisons; }

int Statistics::getMovements() const noexcept { return movements; }

int Statistics::getFunctionCalls() const noexcept { return functionCalls; }

const std::string& Statistics::getAlgorithmName() const noexcept { return algorithmName; }
