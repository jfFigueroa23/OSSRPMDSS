#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "../METODOMULTICRITERIO/MetodoMulticriterio.hpp"
#include "../LIBRERIAS/utilerias/utilerias.hpp"
#include "Superacion.hpp"

using namespace std;

//CREAR MATRICES DE DESEMPEÑO (TEXTO Y REGISTRO)
Superacion::Superacion(int NoAlternativas, int NoCriterios)
{

    NOALTERNATIVAS = NoAlternativas;
    NOCRITERIOS = NoCriterios;

    //MATRIZ DE ENTRADA (LEER ALTERNATIVAS, PESOS Y UMBRALES)
    sMatrizDesempeno = new string * [NOALTERNATIVAS + 7];
    for (int i = 0; i < NOALTERNATIVAS + 7; ++i)
        sMatrizDesempeno[i] = new string[NOCRITERIOS + 1];

    //MATRIZ DE DESEMPEÑO (RENDIMIENTO O PERFORMANCE)
    MatrizDesempeno = new AlternativaMD * [NOALTERNATIVAS];
    for (int i = 0; i < NOALTERNATIVAS; ++i)
        MatrizDesempeno[i] = new AlternativaMD[NOCRITERIOS];
}

//DESTRUIR MATRICES DE DESEMPEÑO (TEXTO Y REGISTRO)
Superacion::~Superacion()
{
    //MATRIZ DE ENTRADA (LEER ALTERNATIVAS, PESOS Y UMBRALES)
    for (int i = 0; i < NOALTERNATIVAS + 7; ++i)
        delete[] sMatrizDesempeno[i];
    delete[] sMatrizDesempeno;

    //MATRIZ DE DESEMPEÑO (RENDIMIENTO O PERFORMANCE)
    for (int i = 0; i < NOALTERNATIVAS; ++i)
        delete[] MatrizDesempeno[i];
    delete[] MatrizDesempeno;
}

//INGRESAR MATRIZ DE DESEMPEÑO DESDE PARAMETRO (TEXTUAL)
bool Superacion::IngresarDatos(string smd)
{

	try
	{

		//Cargar en arreglo, desde el parametro de cadena recibido, las filas de la matriz de desempeño con pesos y umbrales (como texto)
        if (!smd.empty())
		{
			//char buffer[1024];
			char* record, * line;
			int i = 0, j = 0;

			////Carga valor de parametro (matriz CSV)
			char* end_str;
			char* camd = new char[smd.length() + 1];
			strcpy(camd, smd.c_str());

			line = strtok_r(camd, ";", &end_str);

			while (line != NULL)
			{
				char* end_token;

				record = strtok_r(line, ",", &end_token);

				while (record != NULL)
				{
					sMatrizDesempeno[i][j++] = record;

					record = strtok_r(NULL, ",", &end_token);

				}
				++i;
				j = 0;

				line = strtok_r(NULL, ";", &end_str);

			}

			//Distribuye información cargada de archivo en campos de matriz correspondientes [renglon][columna]
			for (int i = 1; i <= NOALTERNATIVAS; i++)
			{
				for (int j = 1; j <= NOCRITERIOS; j++)
				{

					MatrizDesempeno[i - 1][j - 1].etAlternativa = sMatrizDesempeno[i][0].c_str(); 			//Etiqueta alternativa
					MatrizDesempeno[i - 1][j - 1].etCriterio = sMatrizDesempeno[0][j].c_str(); 				//Etiqueta criterio
					MatrizDesempeno[i - 1][j - 1].valor = atof(sMatrizDesempeno[i][j].c_str()); 			//Valor
					MatrizDesempeno[i - 1][j - 1].w = atof(sMatrizDesempeno[NOALTERNATIVAS + 1][j].c_str());	//Peso
					MatrizDesempeno[i - 1][j - 1].p = atof(sMatrizDesempeno[NOALTERNATIVAS + 2][j].c_str());	//Preferencia
					MatrizDesempeno[i - 1][j - 1].q = atof(sMatrizDesempeno[NOALTERNATIVAS + 3][j].c_str());	//Indiferencia
					MatrizDesempeno[i - 1][j - 1].v = atof(sMatrizDesempeno[NOALTERNATIVAS + 4][j].c_str());	//Veto
					MatrizDesempeno[i - 1][j - 1].d = atoi(sMatrizDesempeno[NOALTERNATIVAS + 5][j].c_str());	//Dirección

				}
			}

		}

		return true;

	}
	catch (const exception& e)
	{

		return false;

	}

}
