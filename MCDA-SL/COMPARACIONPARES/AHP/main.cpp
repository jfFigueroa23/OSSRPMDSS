#include "AHP.h"
#include <iostream>
#include <exception>
int main() {
    try {
        AHP ahp("EJEMPLO_AHP.csv");
        ahp.compute();
        ahp.printResults();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
