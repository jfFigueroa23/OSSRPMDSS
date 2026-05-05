#ifndef TOPSIS_HPP
#define TOPSIS_HPP

#include <vector>
#include <string>
#include <set>

// Clase TOPSIS - Biblioteca interna para análisis de decisiones multicriterio
class TOPSIS {
private:
    // Atributos
    std::vector<std::string> attributes;
    std::vector<std::string> candidates;
    std::vector<double> weights;
    std::set<int> benefit_attributes;
    std::vector<std::vector<double>> raw_data;

    // Métodos privados auxiliares
    void normalizeData(std::vector<std::vector<double>>& data, const std::vector<double>& divisors) const;
    void weightData(std::vector<std::vector<double>>& data, const std::vector<double>& weights_vec) const;
    void calculateIdealSolutions(
        const std::vector<std::vector<double>>& data,
        const std::set<int>& benefit_attrs,
        std::vector<double>& a_pos,
        std::vector<double>& a_neg
    ) const;
    void calculateSeparationMeasures(
        const std::vector<std::vector<double>>& data,
        const std::vector<double>& a_pos,
        const std::vector<double>& a_neg,
        std::vector<double>& sp,
        std::vector<double>& sn,
        std::vector<double>& cs
    ) const;
    std::vector<int> rankAccordingTo(const std::vector<double>& values) const;
    std::string printData(
        const std::vector<std::string>& cands,
        const std::vector<std::string>& attrs,
        const std::vector<std::vector<double>>& data,
        const std::string& title
    ) const;

    // Métodos de parsing
    std::vector<std::string> parseStringToVector(const char* str) const;
    std::vector<double> parseStringToDoubleVector(const char* str) const;
    std::set<int> parseStringToSet(const char* str) const;
    std::vector<std::vector<double>> parseRawData(const char* raw_data_str) const;

public:
    // Constructor
    TOPSIS();

    // Destructor
    ~TOPSIS();

    // Método principal de procesamiento
    std::string procesarDatos(
        const char* attributes_str,
        const char* candidates_str,
        const char* weights_str,
        const char* benefit_attributes_str,
        const char* raw_data_str
    );

    // Métodos de acceso a datos
    const std::vector<std::string>& getAttributes() const;
    const std::vector<std::string>& getCandidates() const;
    const std::vector<double>& getWeights() const;
    const std::set<int>& getBenefitAttributes() const;
    const std::vector<std::vector<double>>& getRawData() const;
};

#endif // TOPSIS_HPP

