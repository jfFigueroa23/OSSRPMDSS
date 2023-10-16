#ifndef Superacion_HPP
#define Superacion_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "../METODOMULTICRITERIO/MetodoMulticriterio.hpp"

using namespace std;

class Superacion:public MetodoMulticriterio
{
    public:
        double CORTE;
        Superacion(int NoAlternativas, int NoCriterios);
        ~Superacion();
        bool IngresarDatos(string sMatrizDesempeno);

    protected:
        struct AlternativaMD** MatrizDesempeno;

    private:
        string** sMatrizDesempeno;

};

#endif
