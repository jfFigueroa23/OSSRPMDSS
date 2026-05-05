#ifndef AHP_H
#define AHP_H
#include <vector>
#include <string>
class AHP {
private:
    int n, a;
    std::vector<std::string> criteriaLabels;
    std::vector<std::string> alternativeLabels;
    std::vector<double> criteriaWeights;
    std::vector<std::vector<double>> scores; // a x n
    std::vector<double> totalScores;
    std::vector<double> calcularPuntajeTotal(const std::vector<std::vector<double>>& scores, const std::vector<double>& pesosCriterios);
    int encontrarMejorAlternativa(const std::vector<double>& puntajesTotales);
public:
    AHP(const std::string& csvFile);
    void compute();
    void printResults();
    bool isConsistent() const;
};
#endif // AHP_H
