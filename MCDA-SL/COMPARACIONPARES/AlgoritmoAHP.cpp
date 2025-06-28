//Autores:
// Dacia Melina Sepulveda Gamez
// Norma Idania Bojorquez Garcia

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

// Valores del índice aleatorio (RI) para matrices de 1x1 hasta 9x9
double RI[] = {0.0, 0.0, 0.58, 0.9, 1.12, 1.24, 1.32, 1.41, 1.45}; 

// Funcion para ingresar la matriz de comparacion de criterios
vector<vector<double>> ingresarMatriz(int n) {
    vector<vector<double>> matriz(n, vector<double>(n));
    cout << "Ingrese los valores de la matriz de comparacion de criterios:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "Valor de C" << i+1 << " en comparacion con C" << j+1 << ": ";
            cin >> matriz[i][j];
        }
    }
    return matriz;
}

// Funcion para ingresar la matriz de alternativas
vector<vector<double>> ingresarMatrizAlternativas(int a) {
    vector<vector<double>> matriz(a, vector<double>(a));
    cout << "Ingrese los valores de la matriz de Alternativas:\n";
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < a; ++j) {
            cout << "Valor de A" << i+1 << " en comparacion con A" << j+1 << ": ";
            cin >> matriz[i][j];
        }
    }
    return matriz;
}

// Funcion para normalizar la matriz
vector<vector<double>> normalizarMatriz(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<vector<double>> matrizNormalizada(n, vector<double>(n));
    vector<double> sumaColumnas(n, 0.0);

    // Calcular la suma de cada columna
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            sumaColumnas[j] += matriz[i][j];
        }
    }

    // Normalizar la matriz dividiendo cada elemento de una columna por la suma total de esa columna
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrizNormalizada[i][j] = matriz[i][j] / sumaColumnas[j];
        }
    }

    return matrizNormalizada;
}

// Funcion para calcular el promedio de cada fila
vector<double> calcularPromedioFilas(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    vector<double> promedios(n, 0.0);

    for (int i = 0; i < n; ++i) {
        double sumaFila = 0.0;
        for (int j = 0; j < n; ++j) {
            sumaFila += matriz[i][j];
        }
        promedios[i] = sumaFila / n;
    }

    return promedios;
}


double calcularLambdaMax(const vector<vector<double>>& matrizOriginal, const vector<double>& prioridades) {
    int n = matrizOriginal.size();
    vector<double> resultado(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i] += matrizOriginal[i][j] * prioridades[j];
        }
    }

    double lambdaMax = 0.0;
    for (int i = 0; i < n; ++i) {
        lambdaMax += resultado[i] / prioridades[i];
    }
    return lambdaMax / n;
}

// Funcion para calcular el indice de consistencia (CI)
double calcularCI(double lambdaMax, int n) {
    return (lambdaMax - n) / (n - 1);
}

// Funcion para calcular el indice de consistencia relativa (CR)
double calcularCR(double CI, int n) {
    return CI / RI[n];
}

// Funcion para calcular el puntaje total de cada alternativa ponderado por los criterios
vector<double> calcularPuntajeTotal(const vector<vector<double>>& promediosPorCriterio, const vector<double>& pesosCriterios) {
    int numAlternativas = promediosPorCriterio[0].size(); 
    vector<double> puntajesTotales(numAlternativas, 0.0);  
    
    for (int i = 0; i < pesosCriterios.size(); ++i) {  // Iterar criterios
        for (int j = 0; j < numAlternativas; ++j) {  // Iterar alternativas
            puntajesTotales[j] += promediosPorCriterio[i][j] * pesosCriterios[i];  // Sumar puntajes ponderados
        }
    }

    return puntajesTotales;
}

// Funcion para encontrar la mejor alternativa
int encontrarMejorAlternativa(const vector<double>& puntajesTotales) {
    double maxPuntaje = puntajesTotales[0];
    int mejorAlternativa = 0;
    for (int i = 1; i < puntajesTotales.size(); ++i) {
        if (puntajesTotales[i] > maxPuntaje) {
            maxPuntaje = puntajesTotales[i];
            mejorAlternativa = i;
        }
    }
    return mejorAlternativa + 1;  // +1 porque los índices comienzan desde 0
}

int main() {
    int n, a;
    cout << "Ingrese el tamano de la matriz de comparacion de criterios: ";
    cin >> n;

    // Ingresar la matriz de comparacion de criterios
    vector<vector<double>> matriz = ingresarMatriz(n);

    // Normalizar la matriz de criterios
    vector<vector<double>> matrizNormalizada = normalizarMatriz(matriz);

    // Calcular el promedio de cada fila (vector de prioridades de los criterios)
    vector<double> promedios = calcularPromedioFilas(matrizNormalizada);

    // Mostrar la matriz normalizada y los promedios de cada fila (pesos de los criterios)
    cout << "\nMatriz normalizada de criterios:\n";
    for (const auto& fila : matrizNormalizada) {
        for (double valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }

    cout << "\nPromedio (pesos) de cada criterio:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Criterio " << i+1 << ": " << promedios[i] << endl;
    }

    // Calcular lambda_max
    double lambdaMax = calcularLambdaMax(matriz, promedios);
    cout << "\nLambda_max: " << lambdaMax << endl;

    // Calcular el indice de consistencia (CI)
    double CI = calcularCI(lambdaMax, n);
    cout << "Indice de consistencia (CI): " << CI << endl;

    // Calcular el indice de consistencia relativa (CR)
    double CR = calcularCR(CI, n);
    cout << "Indice de consistencia relativa (CR): " << CR << endl;

    if (CR < 0.1) {
        cout << "La matriz de comparacion es consistente." << endl;
    } else {
        cout << "La matriz de comparacion NO es consistente. Considera revisar las comparaciones." << endl;
    }

    // Vector de vectores para almacenar los promedios de las alternativas por criterio
    vector<vector<double>> promediosPorCriterio;

    // Ingresar las alternativas para cada criterio
    cout << "\nNumero de alternativas a evaluar: ";
    cin >> a;

    for (int i = 0; i < n; ++i) {
        cout << "\nEvaluacion de alternativas para el criterio " << i+1 << ":\n";

        // Matriz de comparacion de alternativas para el criterio actual
        vector<vector<double>> matrizAlternativas = ingresarMatrizAlternativas(a);

        // Normalizar la matriz de alternativas
        vector<vector<double>> matrizNormalizadaAlternativas = normalizarMatriz(matrizAlternativas);

        // Calcular el promedio de cada fila para las alternativas en este criterio
        vector<double> promediosAlternativas = calcularPromedioFilas(matrizNormalizadaAlternativas);

        // Guardar los promedios de las alternativas para este criterio
        promediosPorCriterio.push_back(promediosAlternativas);

        // Mostrar la matriz normalizada y los promedios de las alternativas
        cout << "\nMatriz normalizada de alternativas para el criterio " << i+1 << ":\n";
        for (const auto& fila : matrizNormalizadaAlternativas) {
            for (double valor : fila) {
                cout << valor << " ";
            }
            cout << endl;
        }

        cout << "\nPromedio de cada fila para las alternativas en el criterio " << i+1 << ":\n";
        for (int j = 0; j < a; ++j) {
            cout << "Alternativa " << j+1 << ": " << promediosAlternativas[j] << endl;
        }
    }

    // Calcular el puntaje total de cada alternativa ponderado por los criterios
    vector<double> puntajesTotales = calcularPuntajeTotal(promediosPorCriterio, promedios);

    // Mostrar el puntaje total de cada alternativa
    cout << "\nPuntaje total de cada alternativa:\n";
    for (int i = 0; i < a; ++i) {
        cout << "Alternativa " << i+1 << ": " << puntajesTotales[i] << endl;
    }

    // Encontrar la mejor alternativa
    int mejorAlternativa = encontrarMejorAlternativa(puntajesTotales);
    cout << "\nLa mejor alternativa es la numero: " << mejorAlternativa << endl;

    system("pause");
    return 0;
}
