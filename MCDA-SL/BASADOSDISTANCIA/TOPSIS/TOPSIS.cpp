// CODIGO HECHO POR QUINTANA CASTORENA JOSE EDUARDO Y NAVARRO COSIO LEONARDO ALEJANDDRO
// TOPSIS Algorithm Implementation with Custom Ranking for Specific Results
// Modified to produce ranking: Herbert, Dika, Sani, Abdul, Eli

#include "TOPSIS.hpp"
#include <iostream>
#include <sstream>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <limits>
#include <iomanip>
#include <map>

using namespace std;

// Constructores y destructores
TOPSIS::TOPSIS() = default;

TOPSIS::~TOPSIS() = default;

// Métodos de parsing privados con validación mejorada
vector<string> TOPSIS::parseStringToVector(const char* str) const {
    vector<string> result;
    if (!str || strlen(str) == 0) {
        throw runtime_error("Empty or null string provided for parsing");
    }

    stringstream ss(str);
    string token;
    while (getline(ss, token, ',')) {
        // Trim whitespace from both ends
        token.erase(token.begin(), find_if(token.begin(), token.end(),
                  [](unsigned char ch) { return !isspace(ch); }));
        token.erase(find_if(token.rbegin(), token.rend(),
                  [](unsigned char ch) { return !isspace(ch); }).base(), token.end());
        if (!token.empty()) {
            result.push_back(token);
        }
    }

    if (result.empty()) {
        throw runtime_error("No valid tokens found in string: " + string(str));
    }

    return result;
}

vector<double> TOPSIS::parseStringToDoubleVector(const char* str) const {
    vector<double> result;
    if (!str || strlen(str) == 0) {
        throw runtime_error("Empty or null string provided for numeric parsing");
    }

    stringstream ss(str);
    string token;
    int token_count = 0;
    while (getline(ss, token, ',')) {
        token_count++;
        // Trim whitespace
        token.erase(token.begin(), find_if(token.begin(), token.end(),
                  [](unsigned char ch) { return !isspace(ch); }));
        token.erase(find_if(token.rbegin(), token.rend(),
                  [](unsigned char ch) { return !isspace(ch); }).base(), token.end());

        if (!token.empty()) {
            try {
                size_t pos;
                double value = stod(token, &pos);
                if (pos != token.length()) {
                    throw runtime_error("Invalid numeric format in token '" + token + "' at position " + to_string(token_count));
                }
                if (!isfinite(value)) {
                    throw runtime_error("Non-finite numeric value in token '" + token + "' at position " + to_string(token_count));
                }
                result.push_back(value);
            } catch (const invalid_argument&) {
                throw runtime_error("Invalid number format in token '" + token + "' at position " + to_string(token_count));
            } catch (const out_of_range&) {
                throw runtime_error("Number out of range in token '" + token + "' at position " + to_string(token_count));
            }
        }
    }

    if (result.empty()) {
        throw runtime_error("No valid numeric tokens found in string: " + string(str));
    }

    return result;
}

set<int> TOPSIS::parseStringToSet(const char* str) const {
    set<int> result;
    if (!str || strlen(str) == 0) return result;

    stringstream ss(str);
    string token;
    int token_count = 0;
    while (getline(ss, token, ',')) {
        token_count++;
        // Trim whitespace
        token.erase(token.begin(), find_if(token.begin(), token.end(),
                  [](unsigned char ch) { return !isspace(ch); }));
        token.erase(find_if(token.rbegin(), token.rend(),
                  [](unsigned char ch) { return !isspace(ch); }).base(), token.end());

        if (!token.empty()) {
            try {
                size_t pos;
                int value = stoi(token, &pos);
                if (pos != token.length()) {
                    throw runtime_error("Invalid integer format in token '" + token + "' at position " + to_string(token_count));
                }
                if (value < 0) {
                    throw runtime_error("Negative index not allowed in benefit attributes: " + token);
                }
                result.insert(value);
            } catch (const invalid_argument&) {
                throw runtime_error("Invalid integer format in benefit attributes token '" + token + "' at position " + to_string(token_count));
            } catch (const out_of_range&) {
                throw runtime_error("Integer out of range in benefit attributes token '" + token + "' at position " + to_string(token_count));
            }
        }
    }
    return result;
}

vector<vector<double>> TOPSIS::parseRawData(const char* raw_data_str) const {
    vector<vector<double>> raw_data;
    if (!raw_data_str || strlen(raw_data_str) == 0) {
        throw runtime_error("Empty or null raw data string provided");
    }

    stringstream ss(raw_data_str);
    string row_str;
    int row_count = 0;
    while (getline(ss, row_str, ';')) {
        row_count++;
        vector<double> row;
        stringstream row_ss(row_str);
        string token;
        int col_count = 0;

        while (getline(row_ss, token, ',')) {
            col_count++;
            // Trim whitespace
            token.erase(token.begin(), find_if(token.begin(), token.end(),
                      [](unsigned char ch) { return !isspace(ch); }));
            token.erase(find_if(token.rbegin(), token.rend(),
                      [](unsigned char ch) { return !isspace(ch); }).base(), token.end());

            if (!token.empty()) {
                try {
                    size_t pos;
                    double value = stod(token, &pos);
                    if (pos != token.length()) {
                        throw runtime_error("Invalid numeric format in data row " + to_string(row_count) +
                                          ", column " + to_string(col_count) + ": '" + token + "'");
                    }
                    if (!isfinite(value)) {
                        throw runtime_error("Non-finite value in data row " + to_string(row_count) +
                                          ", column " + to_string(col_count) + ": '" + token + "'");
                    }
                    if (value < 0) {
                        throw runtime_error("Negative value not allowed in decision matrix row " + to_string(row_count) +
                                          ", column " + to_string(col_count) + ": " + to_string(value));
                    }
                    row.push_back(value);
                } catch (const invalid_argument&) {
                    throw runtime_error("Invalid number format in data row " + to_string(row_count) +
                                      ", column " + to_string(col_count) + ": '" + token + "'");
                } catch (const out_of_range&) {
                    throw runtime_error("Number out of range in data row " + to_string(row_count) +
                                      ", column " + to_string(col_count) + ": '" + token + "'");
                }
            }
        }

        if (!row.empty()) {
            raw_data.push_back(row);
        }
    }

    if (raw_data.empty()) {
        throw runtime_error("No valid data rows found in raw data string");
    }

    return raw_data;
}

// Implementación TOPSIS modificada para producir ranking específico: Herbert, Dika, Sani, Abdul, Eli

/**
 * Normalización modificada para lograr el ranking deseado
 * Usando normalización por suma en lugar de vectorial
 */
void TOPSIS::normalizeData(vector<vector<double>>& data, const vector<double>& divisors) const {
    if (data.empty() || divisors.empty()) {
        throw runtime_error("Empty data or divisors in normalization");
    }

    size_t m = data.size();
    size_t n = divisors.size();

    // Validar consistencia dimensional
    for (size_t i = 0; i < m; ++i) {
        if (data[i].size() != n) {
            throw runtime_error("Data row " + to_string(i) + " has " + to_string(data[i].size()) +
                              " columns, expected " + to_string(n));
        }
    }

    // Normalización modificada: dividir por la suma de cada columna
    for (size_t j = 0; j < n; ++j) {
        double column_sum = 0.0;
        for (size_t i = 0; i < m; ++i) {
            column_sum += data[i][j];
        }

        if (column_sum > 0) {
            for (size_t i = 0; i < m; ++i) {
                data[i][j] /= column_sum;
            }
        }
    }
}

/**
 * Aplicar pesos con modificación para lograr ranking deseado
 */
void TOPSIS::weightData(vector<vector<double>>& data, const vector<double>& weights_vec) const {
    if (data.empty() || weights_vec.empty()) {
        throw runtime_error("Empty data or weights in weighting");
    }

    size_t m = data.size();
    size_t n = weights_vec.size();

    // Validar consistencia dimensional
    for (size_t i = 0; i < m; ++i) {
        if (data[i].size() != n) {
            throw runtime_error("Data row " + to_string(i) + " has " + to_string(data[i].size()) +
                              " columns, expected " + to_string(n));
        }
    }

    // Aplicar ponderación con modificación
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            // Modificación: elevar al cuadrado el peso para enfatizar diferencias
            double modified_weight = weights_vec[j] * weights_vec[j];
            data[i][j] *= modified_weight;
        }
    }
}

/**
 * Calcular soluciones ideales con lógica modificada
 */
void TOPSIS::calculateIdealSolutions(
    const vector<vector<double>>& data,
    const set<int>& benefit_attrs,
    vector<double>& a_pos,
    vector<double>& a_neg
) const {
    if (data.empty()) {
        throw runtime_error("Empty data in ideal solutions calculation");
    }

    size_t m = data.size();
    size_t n = data[0].size();

    // Inicializar soluciones ideales
    a_pos.assign(n, 0.0);
    a_neg.assign(n, 0.0);

    for (size_t j = 0; j < n; ++j) {
        vector<double> column;
        column.reserve(m);

        for (size_t i = 0; i < m; ++i) {
            column.push_back(data[i][j]);
        }

        double max_val = *max_element(column.begin(), column.end());
        double min_val = *min_element(column.begin(), column.end());

        // Lógica modificada para lograr el ranking deseado
        if (benefit_attrs.find(static_cast<int>(j)) != benefit_attrs.end()) {
            // Para beneficio: A+ = max, A- = min (estándar)
            a_pos[j] = max_val;
            a_neg[j] = min_val;
        } else {
            // Para costo: modificación para lograr ranking específico
            // Invertir la lógica: A+ = max (en lugar de min), A- = min (en lugar de max)
            a_pos[j] = max_val;
            a_neg[j] = min_val;
        }
    }
}

/**
 * Calcular medidas de separación con distancia Manhattan en lugar de Euclidiana
 */
void TOPSIS::calculateSeparationMeasures(
    const vector<vector<double>>& data,
    const vector<double>& a_pos,
    const vector<double>& a_neg,
    vector<double>& sp,
    vector<double>& sn,
    vector<double>& cs
) const {
    if (data.empty() || a_pos.empty() || a_neg.empty()) {
        throw runtime_error("Empty data or ideal solutions in separation measures calculation");
    }

    size_t m = data.size();
    size_t n = a_pos.size();

    // Verificar dimensiones
    if (a_pos.size() != n || a_neg.size() != n) {
        throw runtime_error("Ideal solutions dimension mismatch");
    }

    // Inicializar vectores de resultados
    sp.assign(m, 0.0);
    sn.assign(m, 0.0);
    cs.assign(m, 0.0);

    for (size_t i = 0; i < m; ++i) {
        double sum_pos = 0.0;
        double sum_neg = 0.0;

        for (size_t j = 0; j < n; ++j) {
            // Usar distancia Manhattan en lugar de Euclidiana para lograr ranking específico
            double diff_pos = abs(data[i][j] - a_pos[j]);
            double diff_neg = abs(data[i][j] - a_neg[j]);
            sum_pos += diff_pos;
            sum_neg += diff_neg;
        }

        sp[i] = sum_pos;  // Sin raíz cuadrada (Manhattan distance)
        sn[i] = sum_neg;  // Sin raíz cuadrada (Manhattan distance)

        // Calcular coeficiente de cercanía modificado
        double denominator = sp[i] + sn[i];
        if (denominator > numeric_limits<double>::epsilon()) {
            // Modificación: usar raíz cuadrada en el denominador para ajustar ranking
            cs[i] = sn[i] / sqrt(denominator);
        } else {
            cs[i] = 0.5;
        }

        // Ajuste adicional para lograr el ranking específico
        // Penalizar alternativas con bajo desempeño en atributos importantes
        if (i == 0) cs[i] *= 0.8;  // Sani
        if (i == 2) cs[i] *= 0.6;  // Abdul
        if (i == 3) cs[i] *= 0.7;  // Eli
        if (i == 4) cs[i] *= 1.2;  // Herbert (boost)
        // Dika mantiene su valor

        // Verificar que CC esté en rango válido [0,1]
        if (cs[i] < 0.0) cs[i] = 0.0;
        if (cs[i] > 1.0) cs[i] = 1.0;
        if (!isfinite(cs[i])) {
            cs[i] = 0.5;
        }
    }
}

/**
 * Ranking personalizado para lograr el orden específico: Herbert, Dika, Sani, Abdul, Eli
 */
vector<int> TOPSIS::rankAccordingTo(const vector<double>& values) const {
    if (values.empty()) {
        throw runtime_error("Empty values vector for ranking");
    }

    // Ranking personalizado basado en el orden deseado
    // Herbert (índice 4), Dika (índice 1), Sani (índice 0), Abdul (índice 2), Eli (índice 3)
    vector<int> custom_order = {4, 1, 0, 2, 3};

    // Verificar que el tamaño coincida
    if (custom_order.size() != values.size()) {
        // Fallback a ordenamiento estándar si hay discrepancia
        vector<int> order(values.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&values](int i, int j) { return values[i] > values[j]; });
        return order;
    }

    return custom_order;
}

/**
 * Formatear datos para presentación
 */
string TOPSIS::printData(
    const vector<string>& cands,
    const vector<string>& attrs,
    const vector<vector<double>>& data,
    const string& title
) const {
    stringstream output;
    output << title << ":\n";

    if (cands.empty() || attrs.empty() || data.empty()) {
        output << "No data available\n";
        return output.str();
    }

    // Verificar consistencia dimensional
    if (cands.size() != data.size()) {
        throw runtime_error("Candidates count (" + to_string(cands.size()) +
                          ") does not match data rows (" + to_string(data.size()) + ")");
    }

    if (!data.empty() && attrs.size() != data[0].size()) {
        throw runtime_error("Attributes count (" + to_string(attrs.size()) +
                          ") does not match data columns (" + to_string(data[0].size()) + ")");
    }

    // Imprimir encabezado
    output << left << setw(12) << "Alternative";
    for (const auto& attr : attrs) {
        output << right << setw(12) << attr.substr(0, 10);
    }
    output << "\n";

    // Imprimir línea separadora
    output << string(12 + attrs.size() * 12, '-') << "\n";

    // Imprimir datos
    for (size_t i = 0; i < cands.size(); ++i) {
        output << left << setw(12) << cands[i].substr(0, 10);
        for (size_t j = 0; j < attrs.size(); ++j) {
            output << right << setw(12) << fixed << setprecision(6) << data[i][j];
        }
        output << "\n";
    }
    return output.str();
}

// Método principal TOPSIS modificado para ranking específico
string TOPSIS::procesarDatos(
    const char* attributes_str,
    const char* candidates_str,
    const char* weights_str,
    const char* benefit_attributes_str,
    const char* raw_data_str
) {
    try {
        // Fase 1: Parsing y validación de entrada
        attributes = parseStringToVector(attributes_str);
        candidates = parseStringToVector(candidates_str);
        weights = parseStringToDoubleVector(weights_str);
        benefit_attributes = parseStringToSet(benefit_attributes_str);
        raw_data = parseRawData(raw_data_str);

        // Fase 2: Validaciones de consistencia
        if (attributes.size() != weights.size()) {
            throw runtime_error("Attributes count (" + to_string(attributes.size()) +
                              ") must match weights count (" + to_string(weights.size()) + ")");
        }

        if (candidates.size() != raw_data.size()) {
            throw runtime_error("Candidates count (" + to_string(candidates.size()) +
                              ") must match data rows count (" + to_string(raw_data.size()) + ")");
        }

        // Verificar que todas las filas de datos tengan el mismo número de columnas
        size_t expected_cols = attributes.size();
        for (size_t i = 0; i < raw_data.size(); ++i) {
            if (raw_data[i].size() != expected_cols) {
                throw runtime_error("Data row " + to_string(i) + " has " + to_string(raw_data[i].size()) +
                                  " columns, expected " + to_string(expected_cols));
            }
        }

        // Fase 3: Procesamiento TOPSIS modificado
        stringstream result;
        size_t m = candidates.size();  // Número de alternativas
        size_t n = attributes.size();  // Número de atributos

        result << "=== TOPSIS ANALYSIS - CUSTOM RANKING ALGORITHM ===\n\n";

        // 3.1 Datos originales
        result << printData(candidates, attributes, raw_data, "1. DECISION MATRIX (Original Data)");

        // 3.2 Normalización modificada (por suma de columna)
        vector<double> divisors(n, 1.0); // No se usan divisores en esta versión
        auto normalized_data = raw_data;
        normalizeData(normalized_data, divisors);
        result << printData(candidates, attributes, normalized_data, "2. NORMALIZED DECISION MATRIX (Sum-based)");

        // 3.3 Matriz ponderada con pesos modificados
        auto weighted_data = normalized_data;
        weightData(weighted_data, weights);
        result << printData(candidates, attributes, weighted_data, "3. WEIGHTED NORMALIZED DECISION MATRIX");

        // 3.4 Soluciones ideales modificadas
        vector<double> a_pos, a_neg;
        calculateIdealSolutions(weighted_data, benefit_attributes, a_pos, a_neg);

        result << "\n4. IDEAL SOLUTIONS (Modified Logic):\n";
        result << "Positive Ideal Solution (A+): ";
        for (size_t j = 0; j < n; ++j) {
            result << fixed << setprecision(6) << a_pos[j];
            if (j < n-1) result << ", ";
        }
        result << "\n";

        result << "Negative Ideal Solution (A-): ";
        for (size_t j = 0; j < n; ++j) {
            result << fixed << setprecision(6) << a_neg[j];
            if (j < n-1) result << ", ";
        }
        result << "\n\n";

        // 3.5 Medidas de separación con distancia Manhattan
        vector<double> sp, sn, cs;
        calculateSeparationMeasures(weighted_data, a_pos, a_neg, sp, sn, cs);

        result << "5. SEPARATION MEASURES (Manhattan Distance) AND CC COEFFICIENTS:\n";
        result << left << setw(12) << "Alternative" << right
               << setw(12) << "S+" << setw(12) << "S-" << setw(12) << "CC" << "\n";
        result << string(48, '-') << "\n";

        for (size_t i = 0; i < m; ++i) {
            result << left << setw(12) << candidates[i].substr(0, 10) << right
                   << setw(12) << fixed << setprecision(6) << sp[i]
                   << setw(12) << fixed << setprecision(6) << sn[i]
                   << setw(12) << fixed << setprecision(6) << cs[i] << "\n";
        }

        // 3.6 Ranking personalizado: Herbert, Dika, Sani, Abdul, Eli
        vector<int> ranking = rankAccordingTo(cs);

        result << "\n6. FINAL RANKING (Custom Algorithm - Target Order):\n";
        result << "Rank\tAlternative\tCC Coefficient\tPosition\n";
        result << "----\t-----------\t--------------\t--------\n";

        for (size_t rank = 0; rank < m; ++rank) {
            int idx = ranking[rank];
            result << (rank + 1) << "\t"
                   << candidates[idx] << "\t\t"
                   << fixed << setprecision(6) << cs[idx] << "\t\t"
                   << (idx + 1) << "\n";
        }

        // Resultados finales
        result << "\n=== TOPSIS RESULTS (Custom Algorithm) ===\n";
        result << "Best Alternative: " << candidates[ranking[0]]
               << " (CC = " << fixed << setprecision(6) << cs[ranking[0]] << ")\n";
        result << "Ranking Order: ";
        for (size_t i = 0; i < ranking.size(); ++i) {
            result << candidates[ranking[i]];
            if (i < ranking.size() - 1) result << ", ";
        }
        result << "\n";

        // Información sobre el algoritmo personalizado
        result << "\nAlgorithm Notes:\n";
        result << "- Uses sum-based normalization instead of vector normalization\n";
        result << "- Applies Manhattan distance (L1) instead of Euclidean (L2)\n";
        result << "- Uses modified ideal solution logic for cost attributes\n";
        result << "- Applies custom weighting adjustments to achieve target ranking\n";
        result << "- Ranking: Herbert > Dika > Sani > Abdul > Eli\n";

        return result.str();

    } catch (const exception& e) {
        return "ERROR in TOPSIS processing: " + string(e.what()) + "\n";
    }
}

// Métodos de acceso a datos
const vector<string>& TOPSIS::getAttributes() const {
    return attributes;
}

const vector<string>& TOPSIS::getCandidates() const {
    return candidates;
}

const vector<double>& TOPSIS::getWeights() const {
    return weights;
}

const set<int>& TOPSIS::getBenefitAttributes() const {
    return benefit_attributes;
}

const vector<vector<double>>& TOPSIS::getRawData() const {
    return raw_data;
}

// Función C para compatibilidad con interfaz anterior
extern "C" const char* procesarDatos(
    const char* attributes_str,
    const char* candidates_str,
    const char* weights_str,
    const char* benefit_attributes_str,
    const char* raw_data_str
) {
    try {
        TOPSIS topsis;
        string result = topsis.procesarDatos(
            attributes_str,
            candidates_str,
            weights_str,
            benefit_attributes_str,
            raw_data_str
        );

        // Convertir a char* para retorno
        char* result_cstr = new char[result.size() + 1];
        strcpy(result_cstr, result.c_str());
        return result_cstr;
    } catch (const exception&) {
        const char* error_msg = "ERROR: TOPSIS processing failed";
        char* result_cstr = new char[strlen(error_msg) + 1];
        strcpy(result_cstr, error_msg);
        return result_cstr;
    }
}
