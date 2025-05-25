#pragma once

#include <map>
#include <optional>
#include <string>
#include <tuple> // Adicionar para std::tuple
#include <utility>

class CalibrationCacheManager {
  private:
    // Nova definição para a chave do cache
    using CacheKey = std::tuple<int, std::string, std::string, std::string>;
    static std::map<CacheKey, std::pair<int, int>> calibrationData;
    static const std::string cacheFilename;
    static bool cacheInitialized;

    // Carrega o cache do arquivo.
    static void loadCacheFromFile();

    // Salva o cache no arquivo (geralmente chamado via atexit).
    static void saveCacheToFileAtExit();

    // Construtor privado para evitar instanciação, pois é uma classe puramente estática.
    CalibrationCacheManager() = delete;

  public:
    // Garante que o cache seja carregado (se ainda não foi) e que o salvamento na saída seja registrado.
    // Deve ser chamado uma vez, por exemplo, no início do programa ou na primeira vez que o cache é acessado.
    static void initialize();

    // Obtém os limiares calibrados para um determinado tamanho de vetor e coeficientes de custo.
    // Retorna std::nullopt se os limiares não estiverem no cache.
    static std::optional<std::pair<int, int>> getThresholds(int vectorSize, double a, double b, double c);

    // Armazena (ou atualiza) os limiares calibrados no cache.
    static void storeThresholds(int vectorSize, double a, double b, double c, int minPartitionSize, int breaksThreshold);

    // Força o salvamento imediato do cache para o arquivo.
    // Útil para testes ou se você não quiser depender apenas do atexit.
    static void forceSaveCache();
};