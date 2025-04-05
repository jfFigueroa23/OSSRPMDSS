#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string.h>
using namespace std;


//Dos metodos, uno de ellos es el de leer el archivo y el otro es con valores ya definidos
/*

Elaborado por:
Betancourt Soto Roberto
Cabanillas Cota Jose Antonio
Asesor:
Figueroa Perez Juan Francisco

*/
extern "C" {
    __declspec(dllexport) float* resolverText(const char* ruta);
    __declspec(dllexport) float* copras(float** tabla, const char** beneficio, float* pesos, int filas, int columnas);
}

float* resolverText(const char* ruta) {
    vector<string> beneficio;
    vector<float> pesos;
    vector<vector<float>> tabla;
    string linea;
    ifstream archivo(ruta);
    if (archivo.is_open()) {
        // Leer la primera línea (cabecera)
        if (getline(archivo, linea)) {
            stringstream ss(linea);
            string valor;

            // Leer cada valor separado por comas
            while (getline(ss, valor, ',')) {
                beneficio.push_back(valor);
            }

            getline(archivo, linea);
            cout << linea << endl;
            stringstream dd(linea);
            while (getline(dd, valor, ',')) {
                pesos.push_back(stof(valor));
            }
        }

        while (getline(archivo, linea)) {
            vector<float> fila_valores;
            stringstream ss(linea);
            string valor;

            // Leer cada valor separado por comas
            while (getline(ss, valor, ',')) {
                fila_valores.push_back(stof(valor));
            }
            tabla.push_back(fila_valores);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }
    archivo.close();

    // Convertir los datos a los tipos adecuados para la función copras
    int filas = tabla.size();
    int columnas = tabla[0].size();
    float** tabla_array = new float*[filas];
    for (int i = 0; i < filas; ++i) {
        tabla_array[i] = new float[columnas];
        for (int j = 0; j < columnas; ++j) {
            tabla_array[i][j] = tabla[i][j];
        }
    }

    const char** beneficio_array = new const char*[beneficio.size()];
    for (size_t i = 0; i < beneficio.size(); ++i) {
        beneficio_array[i] = beneficio[i].c_str();
    }

    float* pesos_array = new float[pesos.size()];
    for (size_t i = 0; i < pesos.size(); ++i) {
        pesos_array[i] = pesos[i];
    }

    float* result = copras(tabla_array, beneficio_array, pesos_array, filas, columnas);

    // Liberar memoria
    for (int i = 0; i < filas; ++i) {
        delete[] tabla_array[i];
    }
    delete[] tabla_array;
    delete[] beneficio_array;
    delete[] pesos_array;
    delete[] result;
    return result;
}

float* copras(float** tabla, const char** beneficio, float* pesos, int filas, int columnas) {
    vector<float> sPlus(filas);
    vector<float> sMinus(filas);
    vector<float> sDiv(filas);
    vector<float> qi(filas);
    vector<float> ui(filas);
    float sMin = FLT_MAX;
    vector<vector<float>> normalizada(filas, vector<float>(columnas));

    // Llenar la tabla normalizada
    for (int i = 0; i < columnas; i++) {
        float sum = 0;
        for (int j = 0; j < filas; j++) {
            sum += tabla[j][i];
        }
        for (int j = 0; j < filas; j++) {
            normalizada[j][i] = tabla[j][i] / sum;
        }
    }

    // Multiplicar por los pesos
    for (int i = 0; i < columnas; i++) {
        for (int j = 0; j < filas; j++) {
            normalizada[j][i] = normalizada[j][i] * pesos[i];
        }
    }

    // Calcular S+i y S-i
    for (int i = 0; i < columnas; i++) {
        if (strcmp(beneficio[i], "B")) {
            for (int k = 0; k < filas; k++) {
                
                sPlus[k] += normalizada[k][i];
            }
        } else {
            for (int k = 0; k < filas; k++) {
                sMinus[k] += normalizada[k][i];
            }
        }
    }

    // Obtener S-Min
    for (int i = 0; i < filas; i++) {
        if (sMinus[i] < sMin) {
            sMin = sMinus[i];
        }
    }

    // Obtener S -min/S -i
    for (int i = 0; i < filas; i++) {
        sDiv[i] = sMin / sMinus[i];
    }

    // Obtener Qi
    for (int i = 0; i < filas; i++) {
        float sum = 0;
        for (int j = 0; j < filas; j++) {
            sum += sMinus[j];
        }
        float arribadiv = sMin * sum;

        sum = 0;
        for (int j = 0; j < filas; j++) {
            sum += sDiv[j];
        }
        float abajodiv = sMinus[i] * sum;

        qi[i] = sPlus[i] + (arribadiv / abajodiv);
        cout << qi[i] << " ";
    }

    // Obtener Ui
    float maxQi = FLT_MIN;
    for (int i = 0; i < filas; i++) {
        if (qi[i] > maxQi) {
            maxQi = qi[i];
        }
    }
    cout << maxQi << "\n";
    for (int i = 0; i < filas; i++) {
        ui[i] = (qi[i] / maxQi) * 100;
    }
    
    // Convertir el resultado a un array de floats
    float* result = new float[ui.size()];
    for (size_t i = 0; i < ui.size(); ++i) {
        result[i] = ui[i];
    }

    return result;
}
int main(){

//Leer archivo
    char* ruta = "C:\\Users\\rober\\Desktop\\COPRAS\\ejemplo.txt";
        
    resolverText(ruta);
    return 0;
    
}