#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "../ELECTREIII/ElectreIII.hpp"

extern "C"
{

    //Interfaz en librería para llamar explotación por flujo neto de ELECTRE III
    char* ElectreIIIExplotarFlujoNeto(int NoAlternativas, int NoCriterios, double Corte, char* smd)
    {
        try {
            ElectreIII E3(NoAlternativas,NoCriterios,Corte);
            E3.IngresarDatos(smd);
            E3.Construir();
            string sResultado = E3.ExplotarFlujoNeto();
            char *cstr = new char[sResultado.length() + 1];
            strcpy(cstr, sResultado.c_str());
            return cstr;
        }
        catch(...) {
            return "Error en librería al llamar a ElectreIIIExplotarFlujoNeto";
        }
    }

    //Interfaz en librería para llamar explotación por destilación de ELECTRE III
    char* ElectreIIIExplotarDestilacion(int NoAlternativas, int NoCriterios, double Corte, char* smd)
    {
        try {
            ElectreIII E3(NoAlternativas,NoCriterios,Corte);
            E3.IngresarDatos(smd);
            E3.Construir();
            string sResultado = E3.ExplotarDestilacion();
            char *cstr = new char[sResultado.length() + 1];
            strcpy(cstr, sResultado.c_str());
            return cstr;
        }
        catch(...) {
            return "Error en librería al llamar a ElectreIIIExplotarDestilacion";
        }
    }

}
