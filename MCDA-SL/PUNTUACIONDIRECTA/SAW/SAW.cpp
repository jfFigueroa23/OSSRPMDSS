#include "SAW.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <vector>
#include <algorithm>
#include <utility>
#include <stdexcept>

SAW::SAW(const std::string& archivo) : numFilas(0), numColumnas(0) {
    // Abre el archivo de texto
    std::ifstream file(archivo);

    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
    }

    // Leer dimensiones de la matriz desde el archivo
    file >> numFilas >> numColumnas;

    // Usar vector de vectores en lugar de matriz estatica
    matriz.resize(numFilas, std::vector<float>(numColumnas));

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            file >> matriz[i][j];
        }
    }
    pesos.resize(numColumnas);
    for (int i = 0; i < numColumnas; i++) {
        file >> pesos[i];
    }

    file.close();

    // Inicializar otras variables
    objetivo.resize(numColumnas);
    newM.resize(numFilas, std::vector<float>(numColumnas));
    sumatoria.resize(numFilas);

    // Inicializamos newM con ceros
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            newM[i][j] = 0;
        }
    }
}

void SAW::calcularObjetivos() {
    // Calculamos los valores objetivos
    std::cout << "Valores mayores o menores de cada columna:" << std::endl;
    for (int i = 0; i < numColumnas; i++) {
        float var = (matriz[0][i] == 0) ? FLT_MAX : -FLT_MAX;
        for (int j = 1; j < numFilas; j++) {
            if ((matriz[j][i] > var && matriz[0][i] == 1) || (matriz[j][i] < var && matriz[0][i] == 0)) {
                var = matriz[j][i];
            }
        }
        objetivo[i] = var;
        std::cout << " " << objetivo[i];
    }
    std::cout << std::endl;
}

void SAW::normalizarMatriz() {
    // división y redondeo
    std::cout << std::fixed << std::setprecision(5); // Configurar la salida con 5 decimales
    std::cout << std::endl << "Matriz con division:" << std::endl;

    for (int j = 1; j < numFilas; j++) {
        for (int i = 0; i < numColumnas; i++) {
            if (matriz[0][i] == 0) {
                // En columnas donde se minimiza (matriz[0][i] == 0), el valor más pequeño se divide por los otros valores
                float min_value = FLT_MAX;
                for (int k = 1; k < numFilas; k++) {
                    if (matriz[k][i] < min_value) {
                        min_value = matriz[k][i];
                    }
                }
                newM[j][i] = min_value / matriz[j][i];
            } else {
                newM[j][i] = matriz[j][i] / objetivo[i];
            }
            std::cout << " " << newM[j][i];
        }
        std::cout << std::endl;
    }
}

void SAW::calcularSumatorias() {
    for (int i = 0; i < numFilas; i++) {
        float suma = 0;
        for (int j = 0; j < numColumnas; j++) {
            suma += newM[i][j] * pesos[j];  // Multiplicacion por pesos
        }
        sumatoria[i] = suma;
        ranking.emplace_back(suma, i);
    }
}

void SAW::ordenarRanking() {
    // Ordenar el ranking en orden descendente
    std::sort(ranking.rbegin(), ranking.rend());
}

void SAW::procesar() {
    // Imprimimos la matriz leida desde el archivo
    std::cout << "Matriz leída desde el archivo:" << std::endl;
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            std::cout << " " << matriz[i][j];
        }
        std::cout << "\n";
    }

    calcularObjetivos();
    normalizarMatriz();
    calcularSumatorias();
    ordenarRanking();
}

void SAW::imprimirResultados() {
    std::cout << "------SUMATORIA y RANKING:------" << std::endl;
    for (int i = 0; i < numFilas - 1; i++) {
        std::cout << "A" << ranking[i].second  << ": " << sumatoria[ranking[i].second] << "\t" << i + 1 << std::endl;
    }
}
