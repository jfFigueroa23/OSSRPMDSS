#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Abre el archivo de texto
    ifstream archivo("SAW.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int numFilas, numColumnas;

    // Leer dimensiones de la matriz desde el archivo
    archivo >> numFilas >> numColumnas;

    // Usar vector de vectores en lugar de matriz estatica
    vector<vector<float>> matriz(numFilas, vector<float>(numColumnas));

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            archivo >> matriz[i][j];
        }
    }
    vector<float> pesos(numColumnas);
    for (int i = 0; i < numColumnas; i++) {
        archivo >> pesos[i];
    }

    archivo.close();

    // Declaramos la matriz objetivo y otras variables
    vector<float> objetivo(numColumnas);
    vector<vector<float>> newM(numFilas, vector<float>(numColumnas));
    vector<float> sumatoria(numFilas);
    float var = 0;
    //float W = 5;

    // Inicializamos newM con ceros
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            newM[i][j] = 0;
        }
    }

    // Imprimimos la matriz leida desde el archivo
    cout << "Matriz leída desde el archivo:" << endl;
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            cout << " " << matriz[i][j];
        }
        cout << "\n";
    }

    // Calculamos los valores objetivos
    cout << "Valores mayores o menores de cada columna:" << endl;
    for (int i = 0; i < numColumnas; i++) {
        var = (matriz[0][i] == 0) ? FLT_MAX : -FLT_MAX;
        for (int j = 1; j < numFilas; j++) {
            if ((matriz[j][i] > var && matriz[0][i] == 1) || (matriz[j][i] < var && matriz[0][i] == 0)) {
                var = matriz[j][i];
            }
        }
        objetivo[i] = var;
        cout << " " << objetivo[i];
    }

    // división y redondeo
    cout << fixed << setprecision(5); // Configurar la salida con 5 decimales
    cout << endl << "Matriz con division:" << endl;

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
            cout << " " << newM[j][i];
        }
        cout << endl;
    }

    vector<pair<float, int>> ranking; // Vector para guardar el ranking

    for (int i = 0; i < numFilas; i++) {
        float suma = 0;
        for (int j = 0; j < numColumnas; j++) {
            suma += newM[i][j] * pesos[j];  // Multiplicacion por pesos
        }
        sumatoria[i] = suma;
        ranking.push_back(make_pair(suma, i));
    }

    // Ordenar el ranking en orden descendente
    sort(ranking.rbegin(), ranking.rend());

    cout << "------SUMATORIA y RANKING:------" << endl;
    for (int i = 0; i < numFilas - 1; i++) {
        cout << "Fila " << ranking[i].second  << ": " << sumatoria[ranking[i].second] << "\t" << i + 1 << endl;
    }

    return 0;
}
