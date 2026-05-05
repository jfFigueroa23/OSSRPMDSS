#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "TOPSIS.hpp"

int main() {
    std::ifstream file("EJEMPLO_TOPSIS.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening EJEMPLO_TOPSIS.csv" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (lines.size() < 5) {
        std::cerr << "CSV file does not have enough lines" << std::endl;
        return 1;
    }

    std::string attributes_str = lines[0];
    std::string candidates_str = lines[1];
    std::string weights_str = lines[2];
    // Assuming benefit_attributes are indices 0,1,3 (price is cost)
    std::string benefit_attributes_str = "0,1,3";
    std::string raw_data_str;
    for (size_t i = 4; i < lines.size(); ++i) {
        if (!lines[i].empty()) {
            if (!raw_data_str.empty()) raw_data_str += ";";
            raw_data_str += lines[i];
        }
    }

    // Crear instancia de la clase TOPSIS
    TOPSIS topsis;
    std::string result = topsis.procesarDatos(
        attributes_str.c_str(),
        candidates_str.c_str(),
        weights_str.c_str(),
        benefit_attributes_str.c_str(),
        raw_data_str.c_str()
    );

    std::cout << result << std::endl;


    return 0;
}
