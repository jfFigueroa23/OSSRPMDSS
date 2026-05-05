#ifndef SAW_H
#define SAW_H

#include <vector>
#include <string>

class SAW {
private:
    int numFilas;
    int numColumnas;
    std::vector<std::vector<float>> matriz;
    std::vector<float> pesos;
    std::vector<float> objetivo;
    std::vector<std::vector<float>> newM;
    std::vector<float> sumatoria;
    std::vector<std::pair<float, int>> ranking;

    void calcularObjetivos();
    void normalizarMatriz();
    void calcularSumatorias();
    void ordenarRanking();

public:
    SAW(const std::string& archivo);
    void procesar();
    void imprimirResultados();
};

#endif // SAW_H
