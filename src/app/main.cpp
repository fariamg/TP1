#include "measurement/Benchmark.h"
#include "datastructures/Vector.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    //* Verifica se o arquivo foi passado como parâmetro
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>\n";
        return 1;
    }

    //* Abre o arquivo
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o file " << argv[1] << "\n";
        return 1;
    }

    //* Função auxiliar para ler um valor por linha
    auto readValue = [&file](auto& value) -> bool {
        std::string line;
        if (!std::getline(file, line)) {
            return false;
        }
        std::istringstream iss(line);
        return (iss >> value) ? true : false;
    };

    //* Lê os parâmetros iniciais (um por line)
    int seed, tam;
    double costThreshold, a, b, c;

    if (!readValue(seed) || !readValue(costThreshold) || !readValue(a) || !readValue(b) || !readValue(c) || !readValue(tam)) {
        std::cerr << "Erro ao ler parâmetros iniciais do file\n";
        return 1;
    }

    //* Cria e preenche o vetor
    Vector V(tam);
    for (int i = 0; i < tam; ++i) {
        int value;
        if (!readValue(value)) {
            std::cerr << "Erro ao ler elemento " << i << " do vetor\n";
            return 1;
        }
        V.push_back(value);
    }


    //* Executa o benchmark
    Benchmark benchmark(a, b, c, seed, costThreshold);
    benchmark.run(V);

    return 0;
}