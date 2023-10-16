#ifndef MetodoMulticriterio_HPP
#define MetodoMulticriterio_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class MetodoMulticriterio
{
    public:
        int NOALTERNATIVAS;
        int NOCRITERIOS;

    protected:


    private:

};

struct AlternativaMD
{
	string etAlternativa;
	string etCriterio;
	double valor;
	double w;
	double p;
	double q;
	double v;
	int d;
};

struct AlternativaMC
{
	double valor;
};

struct AlternativaMDI
{
	double valor;
};

struct AlternativaMCR
{
	double valor;
};

struct AlternativaMT
{
	double valor;
};

struct Ranking
{
	string etAlternativa;
	double score;
};

#endif


