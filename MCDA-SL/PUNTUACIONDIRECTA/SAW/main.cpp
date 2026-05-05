#include <iostream>
#include "SAW.h"

int main() {
    try {
        SAW saw("EJEMPLO_SAW.txt");
        saw.procesar();
        saw.imprimirResultados();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
