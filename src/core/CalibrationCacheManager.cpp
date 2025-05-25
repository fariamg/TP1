#include "core/CalibrationCacheManager.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <tuple>

//* A utilização de biblioteca padrão só é implementada no que tange a funcionalidade do código,
//* não há utilização de recursos facilitadores de implementação de algoritmos ou estruturas de dados,
//* como por exemplo, não há uso de algoritmos da STL ou containers como std::vector, std::list, etc.
//* A biblioteca padrão é utilizada para manipulação de arquivos, formatação de strings e estruturas de dados básicas,
//* como std::map e std::tuple, que são essenciais para o funcionamento do cache de calibração.

//* Definições dos membros estáticos
std::map<std::tuple<int, std::string, std::string, std::string>, std::pair<int, int>> CalibrationCacheManager::calibrationData;
const std::string CalibrationCacheManager::cacheFilename = "calibration_cache.dat";
bool CalibrationCacheManager::cacheInitialized = false;

//* Função auxiliar para converter double para string com precisão fixa
namespace CacheUtils {
std::string doubleToString(double val, int precision = 7) { //* Usando 7 casas de precisão
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << val;
    return oss.str();
}
} 

void CalibrationCacheManager::initialize() {
    if (!cacheInitialized) {
        loadCacheFromFile();
        //* Registra a função saveCacheToFileAtExit para ser chamada quando o programa terminar normalmente.
        std::atexit(saveCacheToFileAtExit);
        cacheInitialized = true;
    }
}

void CalibrationCacheManager::loadCacheFromFile() {
    std::ifstream inFile(cacheFilename);
    if (!inFile.is_open()) {
        std::cout << "INFO: Arquivo de cache '" << cacheFilename << "' não encontrado ou não pôde ser aberto. Iniciando com cache vazio."
                  << std::endl;
        return;
    }

    std::string line;
    int size, mps, lq;
    std::string a_str, b_str, c_str; //* Para ler os coeficientes como string
    int entriesLoaded = 0;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        //* Tenta ler os novos campos da linha
        if (iss >> size >> a_str >> b_str >> c_str >> mps >> lq) {
            std::tuple<int, std::string, std::string, std::string> key = std::make_tuple(size, a_str, b_str, c_str);
            calibrationData[key] = {mps, lq};
            entriesLoaded++;
        } else {
            std::cerr << "AVISO: Linha mal formatada no arquivo de cache ignorada: " << line << std::endl;
        }
    }
    inFile.close();
    if (entriesLoaded > 0) {
        std::cout << "INFO: Cache de calibração carregado de '" << cacheFilename << "' (" << entriesLoaded << " entradas)." << std::endl;
    } else if (inFile.eof() && entriesLoaded == 0) {
        std::cout << "INFO: Arquivo de cache '" << cacheFilename << "' está vazio." << std::endl;
    }
}

void CalibrationCacheManager::saveCacheToFileAtExit() {
    if (calibrationData.empty() && !cacheInitialized) {
        /* Se o cache nunca foi inicializado (e, portanto, está vazio e não foi carregado),
        não há necessidade de criar um arquivo de cache vazio.
        No entanto, se foi inicializado e está vazio, pode ser intencional.
        Para simplificar, sempre tentamos salvar se foi inicializado.*/
    }
    if (!cacheInitialized && calibrationData.empty()) {
        return;
    }

    std::ofstream outFile(cacheFilename);
    if (!outFile.is_open()) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo de cache '" << cacheFilename << "' para escrita." << std::endl;
        return;
    }

    for (const auto& entry : calibrationData) {
        const auto& key_tuple = entry.first;
        outFile << std::get<0>(key_tuple) << " "     //* size
                << std::get<1>(key_tuple) << " "     //* a_str
                << std::get<2>(key_tuple) << " "     //* b_str
                << std::get<3>(key_tuple) << " "     //* c_str
                << entry.second.first << " "         //* mps
                << entry.second.second << std::endl; //* lq
    }
    outFile.close();
    //* Só imprime mensagem de salvamento se realmente havia dados ou se o cache foi usado.
    if (!calibrationData.empty() || cacheInitialized) {
        std::cout << "INFO: Cache de calibração salvo em '" << cacheFilename << "'." << std::endl;
    }
}

std::optional<std::pair<int, int>> CalibrationCacheManager::getThresholds(int vectorSize, double a, double b, double c) {
    initialize();
    std::string a_str = CacheUtils::doubleToString(a);
    std::string b_str = CacheUtils::doubleToString(b);
    std::string c_str = CacheUtils::doubleToString(c);
    std::tuple<int, std::string, std::string, std::string> key = std::make_tuple(vectorSize, a_str, b_str, c_str);

    auto it = calibrationData.find(key);
    if (it != calibrationData.end()) {
        return it->second;
    }
    return std::nullopt;
}

void CalibrationCacheManager::storeThresholds(int vectorSize, double a, double b, double c, int minPartitionSize, int breaksThreshold) {
    initialize();
    std::string a_str = CacheUtils::doubleToString(a);
    std::string b_str = CacheUtils::doubleToString(b);
    std::string c_str = CacheUtils::doubleToString(c);
    std::tuple<int, std::string, std::string, std::string> key = std::make_tuple(vectorSize, a_str, b_str, c_str);

    calibrationData[key] = {minPartitionSize, breaksThreshold};
}

void CalibrationCacheManager::forceSaveCache() {
    saveCacheToFileAtExit();
}