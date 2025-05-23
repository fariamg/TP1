#include "Benchmark.h"
#include "Vector.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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

    // Função auxiliar para ler um valor por linha
    auto lerValor = [&arquivo](auto& valor) -> bool {
        std::string linha;
        if (!std::getline(arquivo, linha)) {
            return false;
        }
        std::istringstream iss(linha);
        return (iss >> valor) ? true : false;
    };

    // Lê os parâmetros iniciais (um por linha)
    int seed, tam;
    double limiarCusto, a, b, c;

    if (!lerValor(seed) || !lerValor(limiarCusto) || !lerValor(a) || !lerValor(b) || !lerValor(c) || !lerValor(tam)) {
        std::cerr << "Erro ao ler parâmetros iniciais do arquivo\n";
        return 1;
    }

    std::cout << "Seed: " << seed << "\nLimiarCusto: " << limiarCusto << "\na: " << a << "\nb: " << b << "\nc: " << c << "\nTamanho: " << tam << "\n";

    // Cria e preenche o vetor
    Vector V(tam);
    for (int i = 0; i < tam; ++i) {
        int valor;
        if (!lerValor(valor)) {
            std::cerr << "Erro ao ler elemento " << i << " do vetor\n";
            return 1;
        }
        V.push_back(valor);
    }

    // Imprime informações iniciais
    int numQuebras = V.getNumBreaks();
    std::cout << "\nTamanho: " << tam << "\nSeed: " << seed << "\nQuebras: " << numQuebras << "\n\n";

    // Executa o benchmark
    Benchmark benchmark(a, b, c, seed, limiarCusto);
    benchmark.run(V);

    return 0;
}