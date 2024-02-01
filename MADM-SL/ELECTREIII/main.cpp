#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include "ElectreIII.hpp"
#include "../LIBRERIAS/utilerias/utilerias.hpp"


using namespace std;

char NOMBREARCHIVO[300];

//INGRESAR MATRIZ DE DESEMPEÑO DESDE ARCHIVO (TEXTUAL)
string CargarArchivo(char sNombreArchivo[])
{
    //Cargar arreglo desde archivo CSV la matriz de desempeño con pesos y umbrales (como cadena de texto)
    ifstream t(sNombreArchivo);
    stringstream buffer;
    buffer << t.rdbuf();
    string sTmp = buffer.str();
    findAndReplaceAll(sTmp, "\n","");
    return sTmp;
}

int main(int argc, char** argv) {

    string sPrueba1, sPrueba2, sPrueba3, sPrueba4, sPrueba5, sPrueba6, sPrueba7;

    //EXPLOTACIÓN POR DESTILACION - CONSTRUCCIÓN CORROBORADA CON J-ELECTRE
    ElectreIII E1(5,5,-1); //CORTE NO ESPECIFICADO EN ARTICULO, ASÍ QUE SE USA EL UMBRAL DE CORTE DEFAULT PROPUESTO POR ROY
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\artesanias.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/artesanias.csv");
    #endif
    E1.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E1.Construir();
    cout << "ARTESANIAS - FLUJO NETO:\n" << E1.ExplotarFlujoNeto() + "\n";
    sPrueba1 = E1.ExplotarDestilacion();
    cout << "ARTESANIAS - DESTILACION:\n" <<  sPrueba1 + "\n";

    //EXPLOTACIÓN POR FLUJO NETO - CORROBORADO COMPLETO CON ARTICULO FUENTE QUE UTILIZÓ DIVIZ
    ElectreIII E2(6,6,0.60); //CORTE ESPECIFICADO EN ARTICULO
    //ElectreIII E2(6,6,0.80); //CORTE ESPECIFICADO EN ARTICULO
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\hoteles.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/hoteles.csv");
    #endif
    E2.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E2.Construir();
    sPrueba2 = E2.ExplotarFlujoNeto();
    cout << "HOTELES - FLUJO NETO:\n" << sPrueba2 + "\n";
    cout << "HOTELES - DESTILACION:\n" << E2.ExplotarDestilacion() + "\n";

    //EXPLOTACIÓN POR FLUJO NETO - SUSTAINABLE ENVIROMENTAL MANAGAMENT (EMS)
    ElectreIII E3(3,3,0.70); //CORTE ESPECIFICADO EN ARTICULO
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\ems.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/ems.csv");
    #endif
    E3.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E3.Construir();
    sPrueba3 = E3.ExplotarFlujoNeto();
    cout << "EMS - FLUJO NETO:\n" << sPrueba3 + "\n";
    cout << "EMS - DESTILACION:\n" << E3.ExplotarDestilacion() + "\n";

    //EXPLOTACIÓN POR DESTILACION - TESIS IPN
    ElectreIII E4(9,6,0.85); //CORTE ESPECIFICADO EN ARTICULO
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\tesis.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/tesis.csv");
    #endif
    E4.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E4.Construir();
    cout << "TESIS - FLUJO NETO:\n" << E4.ExplotarFlujoNeto() + "\n";
    sPrueba4 = E4.ExplotarDestilacion();
    cout << "TESIS - DESTILACION:\n" << sPrueba4 + "\n";

    //EXPLOTACIÓN POR DESTILACION - UNIVERSIDADES (TESIS CASTORENA)
    ElectreIII E5(6,5,-1); //CORTE NO ESPECIFICADO EN ARTICULO, ASÍ QUE SE USA EL UMBRAL DE CORTE DEFAULT PROPUESTO POR ROY
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\universidades.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/universidades.csv");
    #endif
    E5.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E5.Construir();
    cout << "UNIVERSIDADES - FLUJO NETO:\n" << E5.ExplotarFlujoNeto() + "\n";
    sPrueba5 = E5.ExplotarDestilacion();
    cout << "UNIVERSIDADES - DESTILACION:\n" << sPrueba5 + "\n";

    //EXPLOTACIÓN POR DESTILACION - TRANSFERENCIA DE PRODUCTOS (TESIS CASTORENA)
    ElectreIII E6(9,6,-1); //CORTE NO ESPECIFICADO EN ARTICULO, ASÍ QUE SE USA EL UMBRAL DE CORTE DEFAULT PROPUESTO POR ROY
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\tproductos.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/tproductos.csv");
    #endif
    E6.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E6.Construir();
    cout << "TPPRODUCTOS - FLUJO NETO:\n" << E6.ExplotarFlujoNeto() + "\n";
    sPrueba6 = E6.ExplotarDestilacion();
    cout << "TPPRODUCTOS - DESTILACION:\n" << sPrueba6 << + "\n";

    //EXPLOTACIÓN POR DESTILACION - Multicriteria DM using Electre (TESIS CASTORENA)
    ElectreIII E7(9,6,-1); //CORTE NO ESPECIFICADO EN ARTICULO, ASÍ QUE SE USA EL UMBRAL DE CORTE DEFAULT PROPUESTO POR ROY
    #ifdef _WIN32
    strcpy(NOMBREARCHIVO,"D:\\Software\\Sistemas\\Investigacion\\MADM-SL\\ELECTREIII\\pruebas\\MDMelectre.csv");
    #else
    strcpy(NOMBREARCHIVO,"/home/francisco/Software/Sistemas/Investigacion/MADM-SL/ELECTREIII/pruebas/MDMelectre.csv");
    #endif
    E7.IngresarDatos(CargarArchivo(NOMBREARCHIVO));
    E7.Construir();
    cout << "MDMELECTRE - FLUJO NETO:\n" << E7.ExplotarFlujoNeto() + "\n";
    sPrueba7 = E7.ExplotarDestilacion();
    cout << "MDMELECTRE - DESTILACION:\n" << sPrueba7 + "\n\n";

    if (sPrueba1.compare("PRJ1:4;PRJ2:3;PRJ4:2;PRJ3:0;PRJ5:0;") == 0) cout << "ARTESANIAS(DESTILACION): OK\n"; else cout << "ARTESANIAS(DESTILACION): ERROR\n";
    if (sPrueba2.compare("hotel1:2;hotel2:0;hotel4:0;hotel6:0;hotel3:-1;hotel5:-1;") == 0) cout << "HOTELES(FLUJO NETO): OK\n"; else cout << "HOTELES(FLUJO NETO): ERROR\n";
    if (sPrueba3.compare("P1:1;P2:0;P3:-1;") == 0) cout << "EMS(FLUJO NETO): OK\n"; else cout << "EMS(FLUJO NETO): ERROR\n";
    if (sPrueba4.compare("Ee:7;Gg:7;Aa:6;Cc:3;Ff:3;Hh:3;Ii:2;Bb:1;Dd:0;") == 0) cout << "TESIS(DESTILACION): OK\n"; else cout << "TESIS(DESTILACION): ERROR\n";
    if (sPrueba5.compare("U1:4;U5:4;U3:3;U2:1;U6:1;U4:0;") == 0) cout << "UNIVERSIDADES(DESTILACION): OK\n"; else cout << "UNIVERSIDADES(DESTILACION): ERROR\n";
    if (sPrueba6.compare("1Aa:7;4Dd:7;2Bb:5;9Ii:5;3Cc:3;8Hh:3;7Gg:2;6Ff:1;5Ee:0;") == 0) cout << "TPPRODUCTOS(DESTILACION): OK\n"; else cout << "TPPRODUCTOS(DESTILACION): ERROR\n";
    if (sPrueba7.compare("R5:8;R8:7;R3:6;R1:5;R4:4;R6:3;R9:2;R7:1;R2:0;") == 0) cout << "MDMELECTRE(DESTILACION): OK\n"; else cout << "MDMELECTRE(DESTILACION): ERROR\n";

    return 0;

}




