#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include "ElectreIII.hpp"

using namespace std;

string** sMatrizDesempeno;

//CREAR MATRICES O VECTORES DE CONCORDANCIA, DISCORDANCIA, CREDIBILIDAD FUZZY, CREDIBILIDAD CRISP, RANKINGS
//ASCENDENTE Y DESCENDENTE, DESTILACIONES Y TEMPORALES DE USO INTERNO (TEXTO Y REGISTRO)
ElectreIII::ElectreIII(int NoAlternativas, int NoCriterios, double Corte): Superacion(NoAlternativas, NoCriterios)
{

    CORTE = Corte;

    //MATRIZ DE CONCORDANCIA
    MatrizConcordancia = new AlternativaMC * [NOALTERNATIVAS];
    for (int i = 0; i < NOALTERNATIVAS; ++i)
        MatrizConcordancia[i] = new AlternativaMC[NOALTERNATIVAS];

    //VECTOR TEMPORAL PARA GUARDAR SUMA DE CRITERIOS PARA MATRIZ DE CONCORDANCIA
    dCX = new double[NOCRITERIOS];

    //MATRIZ DE DISCORDANCIA
    MatrizDiscordancia = new AlternativaMDI * [(NOCRITERIOS * NOALTERNATIVAS)];
    for (int i = 0; i < (NOCRITERIOS * NOALTERNATIVAS); ++i)
        MatrizDiscordancia[i] = new AlternativaMDI[NOALTERNATIVAS];

    //MATRIZ DE CREDIBILIDAD FUZZY
    MatrizCredibilidad = new AlternativaMCR * [NOALTERNATIVAS];
    for (int i = 0; i < NOALTERNATIVAS; ++i)
        MatrizCredibilidad[i] = new AlternativaMCR[NOALTERNATIVAS];

    //MATRIZ  T (CREDIBILIDAD CRISP)
    MatrizT = new AlternativaMT * [NOALTERNATIVAS];
    for (int i = 0; i < NOALTERNATIVAS; ++i)
        MatrizT[i] = new AlternativaMT[NOALTERNATIVAS];

    //VECTOR PARA RANKING FINAL
    RankingFinal = new Ranking[NOALTERNATIVAS];

    //VECTOR DESTILACIÓN 1
    RankingDescendenteDE = new Ranking[NOALTERNATIVAS];

    //VECTOR DESTILACIÓN 2
    RankingAscendenteDE = new Ranking[NOALTERNATIVAS];

    //VECTOR DESTILACIÓN 3
    RankingTmpDE1 = new Ranking[NOALTERNATIVAS];

    //VECTOR DESTILACIÓN 4
    RankingTmpDE2 = new Ranking[NOALTERNATIVAS];

    //MATRIZ DESTILACIÓN 1
    iRankingMatriz = new int* [NOALTERNATIVAS];
    for (int i = 0; i < NOALTERNATIVAS; ++i)
        iRankingMatriz[i] = new int[NOALTERNATIVAS];

    //VECTOR DESTILACIÓN 6
    iRankingLocal = new double[NOALTERNATIVAS];

}

//DESTRUIR MATRICES O VECTORES DE CONCORDANCIA, DISCORDANCIA, CREDIBILIDAD FUZZY, CREDIBILIDAD CRISP, RANKINGS
//ASCENDENTE Y DESCENDENTE, DESTILACIONES Y TEMPORALES DE USO INTERNO (TEXTO Y REGISTRO)
ElectreIII::~ElectreIII()
{

		//MATRIZ DE CONCORDANCIA
		for (int i = 0; i < NOALTERNATIVAS; ++i)
			delete[] MatrizConcordancia[i];
		delete[] MatrizConcordancia;

		//VECTOR TEMPORAL PARA GUARDAR SUMA DE CRITERIOS PARA MATRIZ DE CONCORDANCIA
		delete[] dCX;

		//MATRIZ DE DISCORDANCIA
		for (int i = 0; i < (NOCRITERIOS * NOALTERNATIVAS); ++i)
			delete[] MatrizDiscordancia[i];
		delete[] MatrizDiscordancia;

		//MATRIZ DE CREDIBILIDAD
		for (int i = 0; i < NOALTERNATIVAS; ++i)
			delete[] MatrizCredibilidad[i];
		delete[] MatrizCredibilidad;

		//MATRIZ T
		for (int i = 0; i < NOALTERNATIVAS; ++i)
			delete[] MatrizT[i];
		delete[] MatrizT;

		//VECTOR PARA RANKING FINAL
		delete[] RankingFinal;

		//VECTOR DESTILACIÓN 1
		delete[] RankingDescendenteDE;

		//VECTOR DESTILACIÓN 2
		delete[] RankingAscendenteDE;

		//VECTOR DESTILACIÓN 3
		delete[] RankingTmpDE1;

		//VECTOR DESTILACIÓN 4
		delete[] RankingTmpDE2;

		//MATRIZ DESTILACIÓN 1
		for (int i = 0; i < NOALTERNATIVAS; ++i)
			delete[] iRankingMatriz[i];
		delete[] iRankingMatriz;

		//VECTOR DESTILACIÓN 6
		delete[] iRankingLocal;

}

//CALCULA MATRIZ DE CONCODANCIA DE LA ETAPA DE CONSTRUCCIÓN
void ElectreIII::CalcularMatrizConcordancia()
{

	double sumac, sumaw;
	int mdx, mdy, altact, altsig, crit, x, y;

	for (altact = 0; altact<NOALTERNATIVAS; altact++)
	{

		mdx = altact;

		for (altsig = 0; altsig<NOALTERNATIVAS; altsig++)
		{

            sumac = 0;
            sumaw = 0;
            mdy = altsig;

            if (altact == altsig)
            	MatrizConcordancia[mdx][mdy].valor = 1;
            else
            {
        		for (crit = 0; crit<NOCRITERIOS; crit++)
        		{
        			if (MatrizDesempeno[altact][crit].d == 1) //Maximizar
        			{

						if (MatrizDesempeno[altact][crit].valor + MatrizDesempeno[altact][crit].q >= MatrizDesempeno[altsig][crit].valor)
							dCX[crit] = (double) 1;
						else if (MatrizDesempeno[altact][crit].valor + MatrizDesempeno[altact][crit].p < MatrizDesempeno[altsig][crit].valor)
							dCX[crit] = (double) 0;
						else dCX[crit] = (double) (MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altsig][crit].valor + MatrizDesempeno[altact][crit].p) / (MatrizDesempeno[altact][crit].p - MatrizDesempeno[altact][crit].q);

        			} else // d == 0 Minimizar
        			{

						if (MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altact][crit].q <= MatrizDesempeno[altsig][crit].valor)
							dCX[crit] = (double) 1;
						else if (MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altact][crit].p > MatrizDesempeno[altsig][crit].valor)
							dCX[crit] = (double) 0;
						else dCX[crit] = (double) (MatrizDesempeno[altsig][crit].valor - MatrizDesempeno[altact][crit].valor + MatrizDesempeno[altact][crit].p) / (MatrizDesempeno[altact][crit].p - MatrizDesempeno[altact][crit].q);

        			}

                    sumac = (double) sumac + (dCX[crit] * (MatrizDesempeno[altact][crit].w));
                    sumaw = (double) sumaw + (MatrizDesempeno[altact][crit].w);
        		}

               MatrizConcordancia[mdx][mdy].valor = (double) (sumac / sumaw);

            }

		}

	}

	char output[50];

	for (x=0; x<NOALTERNATIVAS;x++)
	{
			for (y=0; y<NOALTERNATIVAS;y++)
			{
				sMatrizConcordancia += " | ";
				sprintf(output, "%.2f", MatrizConcordancia[x][y].valor);
				sMatrizConcordancia += output;
			}
			sMatrizConcordancia += " | \n";
	}

}

//CALCULA MATRICES DE DISCONCODANCIA DE LA ETAPA DE CONSTRUCCIÓN
void ElectreIII::CalcularMatrizDiscordancia()
{

    double dX;
    int mdx, mdy, crit, altact, altsig, x, y;

    mdx = 0;
    mdy = 0;

    for (crit = 0; crit< NOCRITERIOS; crit++)
    {

        for (altact = 0; altact< NOALTERNATIVAS; altact++)
        {

            mdx = crit * NOALTERNATIVAS + altact;

            for (altsig = 0; altsig< NOALTERNATIVAS; altsig++)
            {
                mdy = altsig;

                if (altact == altsig)
                	dX = 1;
                else
                {

					if (MatrizDesempeno[altact][crit].d == 1) //Maximizar
					{

						if (MatrizDesempeno[altsig][crit].valor <= ( MatrizDesempeno[altact][crit].valor + MatrizDesempeno[altact][crit].p ) )
							dX = 0;
						else if ( MatrizDesempeno[altsig][crit].valor > ( MatrizDesempeno[altact][crit].valor + MatrizDesempeno[altact][crit].v ))
							dX = 1;
						else dX = (MatrizDesempeno[altsig][crit].valor - MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altact][crit].p)  /  (MatrizDesempeno[altact][crit].v - MatrizDesempeno[altact][crit].p);

					} else // d == 0 Minimizar
					{

						if ( MatrizDesempeno[altsig][crit].valor >= ( MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altact][crit].p ))
							dX = 0;
						else if (MatrizDesempeno[altsig][crit].valor < ( MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altact][crit].v ))
							dX = 1;
						else dX = (MatrizDesempeno[altact][crit].valor - MatrizDesempeno[altsig][crit].valor - MatrizDesempeno[altact][crit].p)  /  (MatrizDesempeno[altact][crit].v - MatrizDesempeno[altact][crit].p);

					}

                }

              MatrizDiscordancia[mdx][mdy].valor = dX;

            }

        }

    }

	char output[5];
//	char output2[5];

	for (x=0; x<NOALTERNATIVAS*NOCRITERIOS;x++)
	{
//			sMatrizDiscordancia += " FILA ";
//			sprintf(output2, "%d", x+1);
//			sMatrizDiscordancia += output2;

			for (y=0; y<NOALTERNATIVAS;y++)
			{
				sMatrizDiscordancia += " | ";
				sprintf(output, "%.2f", MatrizDiscordancia[x][y].valor);
				sMatrizDiscordancia += output;
			}
			sMatrizDiscordancia += " | \n";
	}

}

//CALCULA MATRIZ DE CREDIBILIDAD FUZZY DE LA ETAPA DE CONSTRUCCIÓN
void ElectreIII::CalcularMatrizCredibilidad()
{

    int mdx = 0, mdy = 0, altact = 0, altsig = 0, nmcrit = 0,  x = 0, y = 0;
    double productodisc = 0;

    for (altact = 0; altact < NOALTERNATIVAS; altact++)
    {

        mdx = altact;

        for (altsig = 0; altsig < NOALTERNATIVAS; altsig++)
        {
            mdy = altsig;

			// Calcular credibilidad (igual a concordancia o a partir de valor de formula)
            productodisc = 1;

			for (nmcrit = 0; nmcrit < NOCRITERIOS; nmcrit++)
			{
				if (MatrizDiscordancia[(nmcrit * NOALTERNATIVAS) + mdx][mdy].valor > MatrizConcordancia[mdx][mdy].valor)
					productodisc = productodisc * (1 - MatrizDiscordancia[(nmcrit * NOALTERNATIVAS) + mdx] [mdy].valor ) / (1 - MatrizConcordancia[mdx][mdy].valor);
			}
			productodisc = MatrizConcordancia[mdx][mdy].valor * productodisc;
			MatrizCredibilidad[mdx][mdy].valor = productodisc;

        }

    }

	char output[50];

	for (x=0; x<NOALTERNATIVAS;x++)
	{
			for (y=0; y<NOALTERNATIVAS;y++)
			{
				sMatrizCredibilidad += " | ";
				sprintf(output, "%.2f", MatrizCredibilidad[x][y].valor);
				sMatrizCredibilidad += output;
			}
			sMatrizCredibilidad += " | \n";
	}

}

//LLAMA A LOS MÉTODOS DE LA ETAPA DE CONSTRUCCIÓN (CALCULAR DE CONCORDACIA, DISCORDANCIA Y CREDIBILIDAD)
bool ElectreIII::Construir()
{

	try
	{
		CalcularMatrizConcordancia();
		CalcularMatrizDiscordancia();
		CalcularMatrizCredibilidad();

		return true;

	}
	catch (const exception& e)
	{

		return false;

	}

}

//CALCULA LA MATRIZ T (CREDIBILIDAD CRISP) PARA EL MÉTODO DE EXPLOTACIÓN POR FLUJO NETO (SE LE LLAMA INTERNAMENTE UNA SOLA VEZ)
void ElectreIII::CalcularMatrizTFN(double corte){

	float epsilon = 0.0005f;

	float max = 0;
	//Obtenemos el mayor
	for (int x = 0; x < NOALTERNATIVAS; x++)
	{

		for (int y = 0; y < NOALTERNATIVAS; y++)
		{
			if (x == y)
				continue;
			if (MatrizCredibilidad[x][y].valor > max)
				max = MatrizCredibilidad[x][y].valor;
		}
	}

	max = max - (0.30 - 0.15 * max);

	//Obtenemos el valor de corte
	if (corte == -1) //Calcularlo, si no fue especificado por el usuario
	{
		for (int x = 0; x < NOALTERNATIVAS; x++)
		{
			for (int y = 0; y < NOALTERNATIVAS; y++)
			{
				if (x == y)
					continue;
				if (MatrizCredibilidad[x][y].valor > corte && MatrizCredibilidad[x][y].valor < max && !(fabs(MatrizCredibilidad[x][y].valor - max) < epsilon))
					corte = MatrizCredibilidad[x][y].valor;
			}
		}

        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                MatrizT[x][y].valor = 0;
            }
        }

        //ConstruirT
        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                if (x == y)
                    continue;

                if ((MatrizCredibilidad[x][y].valor > corte && !(fabs(MatrizCredibilidad[x][y].valor - corte) < epsilon)) && (MatrizCredibilidad[x][y].valor - MatrizCredibilidad[y][x].valor > (0.3 - 0.15 * MatrizCredibilidad[x][y].valor))) {
                    MatrizT[x][y].valor = 1;
                }
                else {
                    MatrizT[x][y].valor = 0;
                }

            }
        }

	}
	else
	{

       for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                MatrizT[x][y].valor = 0;
            }
        }

        //ConstruirT
        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                if (x == y)
                    continue;

                if (MatrizCredibilidad[x][y].valor > corte) {
                    MatrizT[x][y].valor = 1;
                }
                else {
                    MatrizT[x][y].valor = 0;
                }

            }
        }

	}

	sMatrizT = "";
	char output[50];

	for (int x=0; x<NOALTERNATIVAS;x++)
	{
			for (int y=0; y<NOALTERNATIVAS;y++)
			{
				sMatrizT += " | ";
				sprintf(output, "%.0f", MatrizT[x][y].valor);
				sMatrizT += output;
			}
			sMatrizT += " | \n";
	}

}

//CALCULA LA MATRIZ T (CREDIBILIDAD CRISP) PARA EL MÉTODO DE EXPLOTACIÓN DESTILACIÓN (SE LE LLAMA INTERNAMENTE VARIAS VECES)
void ElectreIII::CalcularMatrizTDE(Ranking* RankTMP, double corte) {

	float epsilon = 0.0005f;

	float max = 0;
	//Obtenemos el mayor
	for (int x = 0; x < NOALTERNATIVAS; x++)
	{

		//Si es cero significa que se ignora
		if (RankTMP[x].score == 0)
			continue;

		for (int y = 0; y < NOALTERNATIVAS; y++)
		{
			//Si es cero significa que se ignora
			if (RankTMP[y].score == 0)
				continue;
			if (x == y)
				continue;
			if (MatrizCredibilidad[x][y].valor > max)
				max = MatrizCredibilidad[x][y].valor;
		}
	}

	max = max - (0.30 - 0.15 * max);

	//Obtenemos el valor de corte
	if (corte == -1) //Calcularlo, si no fue especificado por el usuario
	{
		for (int x = 0; x < NOALTERNATIVAS; x++)
		{
			if (RankTMP[x].score == 0)
				continue;
			for (int y = 0; y < NOALTERNATIVAS; y++)
			{
				if (RankTMP[y].score == 0)
					continue;
				if (x == y)
					continue;
				if (MatrizCredibilidad[x][y].valor > corte && MatrizCredibilidad[x][y].valor < max && !(fabs(MatrizCredibilidad[x][y].valor - max) < epsilon))
					corte = MatrizCredibilidad[x][y].valor;
			}
		}


        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                MatrizT[x][y].valor = 0;
            }
        }

        //ConstruirT
        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            if (RankTMP[x].score == 0)
                continue;
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                if (RankTMP[y].score == 0)
                    continue;
                if (x == y)
                    continue;

                if ((MatrizCredibilidad[x][y].valor > corte && !(fabs(MatrizCredibilidad[x][y].valor - corte) < epsilon)) && (MatrizCredibilidad[x][y].valor - MatrizCredibilidad[y][x].valor > (0.3 - 0.15 * MatrizCredibilidad[x][y].valor))) {
                    MatrizT[x][y].valor = 1;
                }
                else {
                    MatrizT[x][y].valor = 0;
                }

            }
        }

	}
	else
	{

        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                MatrizT[x][y].valor = 0;
            }
        }

        //ConstruirT
        for (int x = 0; x < NOALTERNATIVAS; x++)
        {
            if (RankTMP[x].score == 0)
                continue;
            for (int y = 0; y < NOALTERNATIVAS; y++)
            {
                if (RankTMP[y].score == 0)
                    continue;
                if (x == y)
                    continue;

                if (MatrizCredibilidad[x][y].valor > corte) {
                    MatrizT[x][y].valor = 1;
                }
                else {
                    MatrizT[x][y].valor = 0;
                }

            }
        }

	}

	sMatrizT = "";
	char output[50];

	for (int x=0; x<NOALTERNATIVAS;x++)
	{
			for (int y=0; y<NOALTERNATIVAS;y++)
			{
				sMatrizT += " | ";
				sprintf(output, "%.0f", MatrizT[x][y].valor);
				sMatrizT += output;
			}
			sMatrizT += " | \n";
	}
}


//FORMATEA SALIDA DE LOS RANKINGS INTERMEDIOS Y FINALES DE LOS DIREFENTES MÉTODOS DE EXPLOTACIÓN
void ElectreIII::FormatearSalidaRanking(string& sRF, struct Ranking* rank, short ordenar)
{
	char output[50];
	if (ordenar)
		sort(rank, rank+NOALTERNATIVAS, CompararRankings);
	for (int alt = 0; alt < NOALTERNATIVAS; alt++)
	{

		sRF += rank[alt].etAlternativa + ":";
		sprintf(output, "%.0f", rank[alt].score);
		sRF += output;
		sRF += ";";
	}

}

//EXPLOTA MATRIZ DE CREDIBILIDAD POR EL MÉTODO DE FLUJO NETO
string ElectreIII::ExplotarFlujoNeto()
{

	int sumWeakness, sumStrength;

	ElectreIII::CalcularMatrizTFN(CORTE);

	for (int alt = 0; alt < NOALTERNATIVAS; alt++)
	{

		sumWeakness = 0;
		sumStrength = 0;

		for (int r = 0;r<NOALTERNATIVAS; r++)
			sumWeakness+= MatrizT[r][alt].valor;

		for (int c = 0;c<NOALTERNATIVAS;c++)
			sumStrength+= MatrizT[alt][c].valor;

		RankingFinal[alt].etAlternativa = MatrizDesempeno[alt][0].etAlternativa;
		RankingFinal[alt].score = sumStrength-sumWeakness;

	}

	ElectreIII::FormatearSalidaRanking(sRankingFinalFN, RankingFinal, 1);

	return sRankingFinalFN;

}

//EXPLOTA MATRIZ DE CREDIBILIDAD POR EL MÉTODO DE DESTILACIÓN
string ElectreIII::ExplotarDestilacion()
{

	string etalt;

	for(int j = 0; j < 2; j++){

		//Llenamos con 1 tmp y los otros con 0
		for(int i=0; i<NOALTERNATIVAS; i++){
			RankingTmpDE1[i].etAlternativa = MatrizDesempeno[i][0].etAlternativa;
			RankingTmpDE1[i].score = 1;
			RankingFinal[i].etAlternativa = MatrizDesempeno[i][0].etAlternativa;
			RankingFinal[i].score = 0;
		}

		bool continuar = false;
		int lugar = 1;
		do{

			for(int i=0; i<NOALTERNATIVAS; i++){
				RankingTmpDE2[i] = RankingTmpDE1[i];
			}
			bool flag = false;

			//Hacemos ciclo mientras exista un empate
			do
			{
				CalcularMatrizTDE(RankingTmpDE2, CORTE);
				flag = RankearTmp(RankingTmpDE2, j);
			}
			while(flag);

			//Ya tenemos el ganador en RankTMPD, lo eliminamos de RankTMP y lo asignamos al rankingFinal
			for(int i = 0; i<NOALTERNATIVAS; i++){
				if(RankingTmpDE2[i].score == 1){
					RankingTmpDE1[i].score = 0;
					etalt = RankingTmpDE1[i].etAlternativa;
					RankingFinal[i].etAlternativa = etalt; //Agregado
					RankingFinal[i].score = lugar;
				}
			}

			lugar++;

			//Verificamos que hayamos terminado o no (si sobro 1)
			int cont = 0;
			int last = 0;
			for(int i=0; i<NOALTERNATIVAS; i++){
				if(RankingFinal[i].score == 0)
				{
					last = i;
				}else{
					cont++;
				}

			}
			cont = NOALTERNATIVAS - cont;
			if(cont == 1){
				RankingFinal[last].etAlternativa = etalt; //Agregado
				RankingFinal[last].score = lugar;
				continuar = false;
			}

			//Verificamos de nuevo en general si falto algo
			for(int i=0; i<NOALTERNATIVAS; i++){
				continuar = false;
				if(RankingFinal[i].score == 0)
				{
					continuar = true;
					break;
				}

			}
		}
		while(continuar);

		//Si es Ascendente ordenamos correctamente
		if(j == 1){
			lugar = 0;
			for(int i=0; i<NOALTERNATIVAS; i++){
				if(RankingFinal[i].score > lugar)
					lugar = RankingFinal[i].score;
			}
			lugar ++;
			for(int i=0; i<NOALTERNATIVAS; i++){
				RankingFinal[i].score = lugar - RankingFinal[i].score;
			}
		}

		for(int i=0; i<NOALTERNATIVAS; i++){
			if(j == 1){
				RankingAscendenteDE[i].score = RankingFinal[i].score;
				RankingAscendenteDE[i].etAlternativa = RankingFinal[i].etAlternativa; //Agregado
			}else{
				RankingDescendenteDE[i].score = RankingFinal[i].score;
				RankingDescendenteDE[i].etAlternativa = RankingFinal[i].etAlternativa; //Agregado
			}
		}
	}

	for(int i=0; i<NOALTERNATIVAS; i++){
		for(int p=0; p<NOALTERNATIVAS; p++){
			iRankingMatriz[i][p] = 0;
		}
	}

	for(int i=0; i<NOALTERNATIVAS; i++){

		for(int p=0; p<NOALTERNATIVAS; p++){
			if(i == p)
				continue;
			//Si es mayor en Descendente
			if(RankingDescendenteDE[i].score > RankingDescendenteDE[p].score){
				//Si es mayor en Descendente y mayor en Ascendente
				if(RankingAscendenteDE[i].score > RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 4;
				//Si es mayor en Descendente e igual en Ascendente
				}else if (RankingAscendenteDE[i].score == RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 4;
				//Si es mayor en Descendente y menor en Ascendente
				}else if(RankingAscendenteDE[i].score < RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 2;
				}
			//Si es menor en Descendente
			}else if(RankingDescendenteDE[i].score < RankingDescendenteDE[p].score){
				//Si es menor en Descendente y mayor en Ascendente
				if(RankingAscendenteDE[i].score > RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 2;
				//Si es menor en Descendente e igual en Ascendente
				}else if (RankingAscendenteDE[i].score == RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 1;
				//Si es menor en Descendente y menor en Ascendente
				}else if(RankingAscendenteDE[i].score < RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 1;
				}
			//Si es igual en Descendente
			}else if(RankingDescendenteDE[i].score == RankingDescendenteDE[p].score){
				//Si es igual en Descendente y mayor en Ascendente
				if(RankingAscendenteDE[i].score > RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 4;
				//Si es igual en Descendente e igual en Ascendente
				}else if (RankingAscendenteDE[i].score == RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 3;
				//Si es igual en Descendente y menor en Ascendente
				}else if(RankingAscendenteDE[i].score < RankingAscendenteDE[p].score){
					iRankingMatriz[i][p] = 1;
				}
			}
		}
	}


	for (int i = 0; i < NOALTERNATIVAS; i++) {
		int suma = 0;
		for (int p = 0; p < NOALTERNATIVAS; p++) {
			if (iRankingMatriz[i][p] == 1)
				suma++;
		}
		RankingFinal[i].etAlternativa = MatrizDesempeno[i][0].etAlternativa;
		RankingFinal[i].score = suma;
	}

	ElectreIII::FormatearSalidaRanking(sRankingAscendenteDE, RankingAscendenteDE, 0);
	ElectreIII::FormatearSalidaRanking(sRankingDescendenteDE, RankingDescendenteDE, 0);
	ElectreIII::FormatearSalidaRanking(sRankingFinalDE, RankingFinal, 1);

	return sRankingFinalDE;

}

//CALCULO DE RANKINGS TEMPORALES USADOS INTERNAMENTE PARA DESTILACIÓN
bool ElectreIII::RankearTmp(Ranking* RankTMP, int flagg){

	float mayor = 10;
	if(flagg < 1)
		mayor = 0;

	for(int i=0; i<NOALTERNATIVAS; i++){
		iRankingLocal[i] = 0;
	}

	//Descendente
	for(int f = 0; f < NOALTERNATIVAS; f++){
		if(RankTMP[f].score == 0)
			continue;

		float sum = 0;
		//Hacemos la suma
		for (int c = 0; c < NOALTERNATIVAS; c++)
		{
			if(RankTMP[f].score == 0)
			continue;
			sum += MatrizT[f][c].valor;
		}

		//Hacemos la resta
		for (int c = 0; c < NOALTERNATIVAS; c++)
		{
			if(RankTMP[f].score == 0)
			continue;
			sum -= MatrizT[c][f].valor;
		}

		iRankingLocal[f] = sum;
		if(flagg < 1){
			if(sum >= mayor)
				mayor = sum;
		}else{
			if(sum <= mayor)
			mayor = sum;
		}

	}

	//verificamos si hay empate total
	bool empate = false;
	for(int i = 0; i < NOALTERNATIVAS; i++){
		if(iRankingLocal[i] != 0)
			break;
		if(i + 1 == NOALTERNATIVAS)
			empate = true;
	}
	if(empate)
		return false;

	//Checamos que no haya empate
	int cont = 0;
	for(int i = 0; i < NOALTERNATIVAS; i++){
		if(iRankingLocal[i] == mayor){
			RankTMP[i].score = 1;
			cont++;
		}else{
			RankTMP[i].score = 0;
		}
	}

	if(cont > 1 && mayor != 0)
		return true;
	else return false;
}

bool ElectreIII::CompararRankings(Ranking lhs, Ranking rhs) { return lhs.score > rhs.score; }
string ElectreIII::ObtenerMatrizConcordancia() { return sMatrizConcordancia; }
string ElectreIII::ObtenerMatrizDiscordancia() { return sMatrizDiscordancia; }
string ElectreIII::ObtenerMatrizCredibilidad() { return sMatrizCredibilidad; }
