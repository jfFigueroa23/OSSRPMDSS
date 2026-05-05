#include "AHP.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
std::vector<double> AHP::calcularPuntajeTotal(const std::vector<std::vector<double>>& scores, const std::vector<double>& pesosCriterios) {
    int numAlternativas = scores.size();
    int numCriterios = scores[0].size();
    std::vector<double> puntajesTotales(numAlternativas, 0.0);
    for (int j = 0; j < numAlternativas; ++j) {
        for (int i = 0; i < numCriterios; ++i) {
            puntajesTotales[j] += scores[j][i] * pesosCriterios[i];
        }
    }
    return puntajesTotales;
}
int AHP::encontrarMejorAlternativa(const std::vector<double>& puntajesTotales) {
    double maxPuntaje = puntajesTotales[0];
    int mejorAlternativa = 0;
    for (size_t i = 1; i < puntajesTotales.size(); ++i) {
        if (puntajesTotales[i] > maxPuntaje) {
            maxPuntaje = puntajesTotales[i];
            mejorAlternativa = i;
        }
    }
    return mejorAlternativa + 1;
}
AHP::AHP(const std::string& csvFile) {
    std::ifstream file(csvFile);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + csvFile);
    }
    std::string line;
    // First row: criteria labels
    std::getline(file, line);
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        criteriaLabels.push_back(token);
    }
    n = criteriaLabels.size();
    // Second row: criteria weights
    std::getline(file, line);
    std::stringstream ss2(line);
    criteriaWeights.resize(n);
    for (int i = 0; i < n; ++i) {
        std::getline(ss2, token, ',');
        criteriaWeights[i] = std::stod(token);
    }
    // Third row: alternative labels
    std::getline(file, line);
    std::stringstream ss3(line);
    while (std::getline(ss3, token, ',')) {
        alternativeLabels.push_back(token);
    }
    a = alternativeLabels.size();
    // Then, a rows of scores, each with n values
    scores.resize(a, std::vector<double>(n));
    for (int i = 0; i < a; ++i) {
        std::getline(file, line);
        std::stringstream ss4(line);
        for (int j = 0; j < n; ++j) {
            std::getline(ss4, token, ',');
            scores[i][j] = std::stod(token);
        }
    }
}
void AHP::compute() {
    // Criteria weights are already provided
    // Calculate total scores
    totalScores = calcularPuntajeTotal(scores, criteriaWeights);
}
void AHP::printResults() {
    std::cout << "Criteria Weights:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << criteriaLabels[i] << ": " << criteriaWeights[i] << std::endl;
    }
    std::cout << "Total Scores:" << std::endl;
    for (int i = 0; i < a; ++i) {
        std::cout << alternativeLabels[i] << ": " << totalScores[i] << std::endl;
    }
    int best = encontrarMejorAlternativa(totalScores);
    std::cout << "Best alternative: " << alternativeLabels[best-1] << std::endl;
}
bool AHP::isConsistent() const {
    // Since weights are provided directly, assume consistent
    return true;
}
