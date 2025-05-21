// #include "measurement/Benchmark.h"
// #include "core/UniversalSorter.h"

// Benchmark::Benchmark(double a, double b, double c, int seed, int costThreshold)
//     : timer(), a(a), b(b), c(c), seed(seed), costThreshold(costThreshold) {}

// void Benchmark::run(Vector& V) {
//     timer.start();

//     UniversalSorter sorter(V);

//     int partitionThreshold = sorter.determinePartitionThreshold(costThreshold, a, b, c);

//     std::cout << "Benchmark concluído:\n";
//     std::cout << "Limiar de partição: " << partitionThreshold << "\n";
//     std::cout << "Tempo decorrido: " << timer.elapsedSeconds() << " segundos\n";
// }