#ifndef MetodoAsignacionPesos_HPP
#define MetodoAsignacionPesos_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "../METODOASIGNACIONPESOS/MetodoAsignacionPesos.hpp"

using namespace std;

class Pct:public MetodoAsignacionPesos
{
    public:
        Pct(int NoCriterios);
        ~Pct();
        bool IngresarDatos(char sNombreArchivo[]);
        bool IngresarDatos(string smpct);
        string CalcularPesos();

    protected:


    private:
        string** sMatrizPCT;
        double** MatrizPCT;
        string* VectorCriterios;
        string sPesosPCT;

};

#endif
