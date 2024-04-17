#ifndef Promethee_HPP
#define Promethee_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "../SUPERACION/Superacion.hpp"

using namespace std;

class Promethee:public Superacion
{
    public:
        Promethee(int NoAlternativas, int NoCriterios, double Corte);
        ~Promethee();

    protected:

    private:
};
#endif
