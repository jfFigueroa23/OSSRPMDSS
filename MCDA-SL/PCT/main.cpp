#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "pct.hpp";

using namespace std;

char NOMBREARCHIVO[300];

int main(int argc, char** argv) {

    string sPrueba1, sPrueba2;

    //PRUEBA DE PESOS 1
    Pct P1(8);
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\PCT\\pruebas\\pct1.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/PCT/pruebas/pct1.csv");
    #endif
    P1.IngresarDatos(NOMBREARCHIVO);
    sPrueba1 = P1.CalcularPesos();
    cout << "PESOS 1:\n" <<  sPrueba1 + "\n";

    //PRUEBA DE PESOS 2
    Pct P2(8);
	string p2 = "-,C1, C2, C3, C4, C5, C6, C7, C8;"
               "C1,0, 1, 1, 1, 1, 1, 1, 1;"
			   "C2,-1, 0, 1, 1, 1, 1, 1, 1;"
			   "C3,-1, -1, 0, 1, -1, -1, -1, -1;"
			   "C4,-1, -1, -1, 0, 1, 0, 1, 1;"
			   "C5,-1, -1, 1, -1, 0, -1, 1, -1;"
			   "C6,-1, -1, 1, 0, 1, 0, 1, -1;"
			   "C7,-1, -1, 1, -1, -1, -1, 0, 1;"
			   "C8,-1, -1, 1, -1, 1, 1, -1, 0;";
    P2.IngresarDatos(p2);
    sPrueba2 = P2.CalcularPesos();
    cout << "PESOS 2:\n" <<  sPrueba2 + "\n";

    if (sPrueba1.compare("G1:0.103\nG2:0.103\nG3:0.172\nG4:0.172\nG5:0.034\nG6:0.069\nG7:0.172\nG8:0.172\n") == 0) cout << "Prueba 1: OK\n"; else cout << "Prueba 1: ERROR\n";
    if (sPrueba2.compare("C1:0.26\nC2:0.22\nC3:0.18\nC4:0.11\nC5:0.11\nC6:0.04\nC7:0.04\nC8:0.04\n") == 0) cout << "Prueba 2: OK\n"; else cout << "Prueba 2: ERROR\n";

	return 0;
}
