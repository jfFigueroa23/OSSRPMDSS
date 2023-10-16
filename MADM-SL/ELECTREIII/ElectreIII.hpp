#ifndef ElectreIII_HPP
#define ElectreIII_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "../SUPERACION/Superacion.hpp"

using namespace std;

class ElectreIII:public Superacion
{
    public:
        ElectreIII(int NoAlternativas, int NoCriterios, double Corte);
        ~ElectreIII();
        bool Construir();
        string ObtenerMatrizConcordancia();
        string ObtenerMatrizDiscordancia();
        string ObtenerMatrizCredibilidad();
        string ExplotarFlujoNeto();
        string ExplotarDestilacion();

    protected:


    private:
        struct AlternativaMC** MatrizConcordancia;
        struct AlternativaMDI** MatrizDiscordancia;
        struct AlternativaMCR** MatrizCredibilidad;
        struct AlternativaMT** MatrizT;
        struct Ranking* RankingAscendenteDE;
        struct Ranking* RankingDescendenteDE;
        struct Ranking* RankingFinal;
        struct Ranking* RankingTmpDE1;
        struct Ranking* RankingTmpDE2;
        string sMatrizConcordancia;
        string sMatrizDiscordancia;
        string sMatrizCredibilidad;
        string sMatrizT;
        string sRankingFinalFN;
        string sRankingAscendenteDE;
        string sRankingDescendenteDE;
        string sRankingFinalDE;
        int** iRankingMatriz;
        double* iRankingLocal;
        double* dCX;
        void CalcularMatrizConcordancia();
        void CalcularMatrizDiscordancia();
        void CalcularMatrizCredibilidad();
        void CalcularMatrizTFN(double corte);
        void CalcularMatrizTDE(Ranking* RankTMP, double corte);
        static bool CompararRankings(Ranking lhs, Ranking rhs);
        void FormatearSalidaRanking(string& sRF, struct Ranking* rank, short ordenar);
        bool RankearTmp(Ranking* RankTMP, int flagg);

};

#endif
