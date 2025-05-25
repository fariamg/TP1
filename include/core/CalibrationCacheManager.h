#pragma once

#include <map>
#include <optional>
#include <string>
#include <tuple>
#include <utility>

//@ Cuida do cache de calibração, armazenando e recuperando limiares calibrados
class CalibrationCacheManager {
  private:
    //@Estrutura de chave para o cache, composta por tamanho do vetor e coeficientes de custo.
    using CacheKey = std::tuple<int, std::string, std::string, std::string>;

    //@ Mapa que armazena os limiares calibrados, mapeando a chave para um par de inteiros (minPartitionSize, breaksThreshold).
    static std::map<CacheKey, std::pair<int, int>> calibrationData;

    //@ Nome do arquivo onde o cache será salvo.
    static const std::string cacheFilename;
    static bool cacheInitialized;

    //@ Carrega o cache do arquivo.
    static void loadCacheFromFile();

    //@ Salva o cache no arquivo (geralmente chamado via atexit).
    static void saveCacheToFileAtExit();

    //@ Construtor privado para evitar instanciação, pois é uma classe puramente estática.
    CalibrationCacheManager() = delete;

  public:
    // @ Metodo estático para inicializar o cache, carregando os dados do arquivo se necessário.
    static void initialize();

    //@ Obtém os limiares calibrados para um determinado tamanho de vetor e coeficientes de custo.
    static std::optional<std::pair<int, int>> getThresholds(int vectorSize, double a, double b, double c);

    //@ Armazena (ou atualiza) os limiares calibrados no cache.
    static void storeThresholds(int vectorSize, double a, double b, double c, int minPartitionSize, int breaksThreshold);

    //@ Força o salvamento imediato do cache para o arquivo.
    static void forceSaveCache();
};