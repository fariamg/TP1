#include "datastructures/Vector.h"
#include "measurement/Benchmark.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    // Verifica se o arquivo foi passado como parâmetro
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>\n";
        return 1;
    }

    // Abre o arquivo
    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << argv[1] << "\n";
        return 1;
    }

    // Lê os parâmetros do arquivo
    double a = 0, b = 0, c = 0, limiarCusto = 0;
    int tam = 0, seed = 0;

    arquivo >> seed >> limiarCusto >> a >> b >> c >> tam;

    std::cout << "Seed: " << seed << ", LimiarCusto: " << limiarCusto << ", a: " << a << ", b: " << b << ", c: " << c << ", Tamanho: " << tam << "\n";

    // Cria o vetor
    Vector V(tam);
    for (int i = 0; i < tam; ++i) {
        int value;
        arquivo >> value;
        V.push_back(value);
    }

    // Fecha o arquivo
    arquivo.close();

    // Imprime informações iniciais
    int numBreaks = V.getNumBreaks();
    std::cout << "size " << tam << " seed " << seed << " breaks " << numBreaks << "\n\n";

    // Cria o benchmark e executa
    Benchmark benchmark(a, b, c, seed, limiarCusto);
    benchmark.run(V);

    return 0;
}