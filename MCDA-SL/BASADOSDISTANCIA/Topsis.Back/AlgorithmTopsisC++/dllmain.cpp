// CODIGO HECHO POR QUINTANA CASTORENA JOSE EDUARDO Y NAVARRO COSIO LEONARDO ALEJANDDRO

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstring>
#include "dll.h"

using namespace std;

vector<int> rank_according_to(const vector<double>& values) {
    vector<int> order(values.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&values](int i, int j) { return values[i] > values[j]; });
    return order;
}

vector<string> parseStringToVector(const char* str) {
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ',')) {
        result.push_back(token);
    }
    return result;
}

vector<double> parseStringToDoubleVector(const char* str) {
    vector<double> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ',')) {
        result.push_back(stod(token));
    }
    return result;
}

set<int> parseStringToSet(const char* str) {
    set<int> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ',')) {
        result.insert(stoi(token));
    }
    return result;
}

vector<vector<double>> parseRawData(const char* raw_data_str) {
    vector<vector<double>> raw_data;
    stringstream ss(raw_data_str);
    string row_str;
    while (getline(ss, row_str, ';')) {
        vector<double> row;
        stringstream row_ss(row_str);
        string token;
        while (getline(row_ss, token, ',')) {
            row.push_back(stod(token));
        }
        raw_data.push_back(row);
    }
    return raw_data;
}

void normalizeData(vector<vector<double>>& raw_data, const vector<double>& divisors) {
    size_t m = raw_data.size();
    size_t n = divisors.size();

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            raw_data[i][j] /= divisors[j];
        }
    }
}

void weightData(vector<vector<double>>& raw_data, const vector<double>& weights) {
    size_t m = raw_data.size();
    size_t n = weights.size();

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            raw_data[i][j] *= weights[j];
        }
    }
}

void calculateIdealSolutions(
        const vector<vector<double>>& raw_data,
        const set<int>& benefit_attributes,
        vector<double>& a_pos,
        vector<double>& a_neg
) {
    size_t m = raw_data.size();
    size_t n = a_pos.size();

    for (size_t j = 0; j < n; ++j) {
        vector<double> column;
        for (size_t i = 0; i < m; ++i) {
            column.push_back(raw_data[i][j]);
        }

        double max_val = *max_element(column.begin(), column.end());
        double min_val = *min_element(column.begin(), column.end());

        if (benefit_attributes.find(j) != benefit_attributes.end()) {
            a_pos[j] = max_val;
            a_neg[j] = min_val;
        } else {
            a_pos[j] = min_val;
            a_neg[j] = max_val;
        }
    }
}

void calculateSeparationMeasures(
        const vector<vector<double>>& raw_data,
        const vector<double>& a_pos,
        const vector<double>& a_neg,
        vector<double>& sp,
        vector<double>& sn,
        vector<double>& cs
) {
    size_t m = raw_data.size();
    size_t n = a_pos.size();

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            double diff_pos = raw_data[i][j] - a_pos[j];
            double diff_neg = raw_data[i][j] - a_neg[j];
            sp[i] += pow(diff_pos, 2);
            sn[i] += pow(diff_neg, 2);
        }
        sp[i] = sqrt(sp[i]);
        sn[i] = sqrt(sn[i]);
        cs[i] = sn[i] / (sp[i] + sn[i]);
    }
}

string printData(
        const vector<string>& candidates,
        const vector<string>& attributes,
        const vector<vector<double>>& data,
        const string& title
) {
    stringstream output;
    output << title << ":\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        output << candidates[i] << "\t";
        for (size_t j = 0; j < attributes.size(); ++j) {
            output << data[i][j] << "\t";
        }
        output << endl;
    }
    return output.str();
}

extern "C" EXPORT const char* procesarDatos(
        const char* attributes_str,
        const char* candidates_str,
        const char* weights_str,
        const char* benefit_attributes_str,
        const char* raw_data_str
) {
    // Convertir strings a estructuras de datos apropiadas
    vector<string> attributes = parseStringToVector(attributes_str);
    vector<string> candidates = parseStringToVector(candidates_str);
    vector<double> weights = parseStringToDoubleVector(weights_str);
    set<int> benefit_attributes = parseStringToSet(benefit_attributes_str);
    vector<vector<double>> raw_data = parseRawData(raw_data_str);

    // Stringstream para capturar todas las salidas
    stringstream result;

    // Imprimir datos sin procesar
    result << printData(candidates, attributes, raw_data, "Datos sin procesar");

    // Normalizar datos
    size_t n = attributes.size();
    vector<double> divisors(n);
    for (size_t j = 0; j < n; ++j) {
        vector<double> column;
        for (size_t i = 0; i < raw_data.size(); ++i) {
            column.push_back(raw_data[i][j]);
        }
        divisors[j] = sqrt(inner_product(column.begin(), column.end(), column.begin(), 0.0));
    }
    normalizeData(raw_data, divisors);
    result << printData(candidates, attributes, raw_data, "Datos Normalizados");

    // Ponderar datos
    weightData(raw_data, weights);
    result << printData(candidates, attributes, raw_data, "Datos Ponderados");

    // Calcular soluciones ideales positivas y negativas
    vector<double> a_pos(n, 0.0);
    vector<double> a_neg(n, 0.0);
    calculateIdealSolutions(raw_data, benefit_attributes, a_pos, a_neg);

    // Imprimir soluciones ideales
    result << "\nSoluciones ideales positivas y negativas:\n";
    result << "A+\t";
    for (const auto& val : a_pos) {
        result << val << "\t";
    }
    result << endl;

    result << "A-\t";
    for (const auto& val : a_neg) {
        result << val << "\t";
    }
    result << endl;

    // Calcular medidas de separación
    vector<double> sp(raw_data.size(), 0.0);
    vector<double> sn(raw_data.size(), 0.0);
    vector<double> cs(raw_data.size(), 0.0);
    calculateSeparationMeasures(raw_data, a_pos, a_neg, sp, sn, cs);

    // Imprimir medidas de separación
    result << "\nMedidas de separacion:\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        result << candidates[i] << "\t" << "S+: " << sp[i] << "\t" << "S-: " << sn[i] << "\t" << "C+: " << cs[i] << endl;
    }

    // Ordenar según las medidas de separación
    vector<int> cs_order = rank_according_to(cs);

    // Imprimir orden clasificado
    result << "\nOrden clasificado:\n";
    for (size_t i = 0; i < candidates.size(); ++i) {
        result << candidates[cs_order[i]] << "\t" << "C+: " << cs[cs_order[i]] << endl;
    }

    // Imprimir el mejor candidato/alternativa según C*
    result << "El mejor candidato/alternativa segun C* es: " << candidates[cs_order[0]] << endl;

    // Imprimir preferencias en orden descendente
    result << "Las preferencias en orden descendente son: ";
    for (size_t i = 0; i < candidates.size(); ++i) {
        result << candidates[cs_order[i]];
        if (i < candidates.size() - 1) {
            result << ", ";
        }
    }
    result << "." << endl;

    // Convertir el resultado a char* para retornar
    string result_str = result.str();
    char* result_cstr = new char[result_str.size() + 1];
    strcpy(result_cstr, result_str.c_str());
    return result_cstr;
}
