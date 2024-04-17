#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "pct.hpp";

using namespace std;

//CREAR MATRICES DE CRITERIOS (TEXTO Y REGISTRO)
Pct::Pct(int NoCriterios)
{

    NOCRITERIOS = NoCriterios;

    //MATRIZ DE ENTRADA (LEER CRITERIOS)
    sMatrizPCT = new string * [NOCRITERIOS+1];
    for (int i = 0; i < NOCRITERIOS+1; ++i)
        sMatrizPCT[i] = new string[NOCRITERIOS + 1];

    //MATRIZ CONSTRUCCIÓN PERSONAL
    MatrizPCT = new double* [NOCRITERIOS];
    for (int i = 0; i < NOCRITERIOS; ++i)
        MatrizPCT[i] = new double[NOCRITERIOS + 3];

    //VECTOR CRITERIOS
    VectorCriterios = new string[NOCRITERIOS];

}

//DESTRUIR MATRICES DE CRITERIOS (TEXTO Y REGISTRO)
Pct::~Pct()
{
    //MATRIZ ENTRADA
    for (int i = 0; i < NOCRITERIOS+1; ++i)
        delete[] sMatrizPCT[i];
    delete[] sMatrizPCT;

    //MATRIZ CONSTRUCCIÓN PERSONAL
    for (int i = 0; i < NOCRITERIOS; ++i)
        delete[] MatrizPCT[i];
    delete[] MatrizPCT;

    //CRITERIOS
    delete[] VectorCriterios;

}

//INGRESAR MATRIZ DE CRITERIOS DESDE ARCHIVO (TEXTUAL)
bool Pct::IngresarDatos(char sNombreArchivo[])
{

	try
	{
		//Cargar en arreglo, desde archivo CSV, las filas de la matriz de criterios
		FILE* file = fopen(sNombreArchivo, "r");
		if (file)
		{
			char buffer[1024];
			char* record, * line;
			int ren = 0, col = 0;

			//Carga archivo CSV
			while ((line = fgets(buffer, sizeof(buffer), file)) != NULL)
			{
				record = strtok(line, ",");
				while (record != NULL)
				{
					sMatrizPCT[ren][col] = record; //elemento matriz entrada
					record = strtok(NULL, ",");
					col++;
				}
				col = 0;
				ren++;
			}

            fclose(file);

			//Distribuye información pasada como parametro en matrices correspondientes
			for (int i = 1; i <= NOCRITERIOS; i++)
			{
				for (int j = 1; j <= NOCRITERIOS; j++)
				{
					MatrizPCT[i - 1][j - 1] = atof(sMatrizPCT[i][j].c_str()); //Valor [renglon][columna]
                }
                VectorCriterios[i-1] = sMatrizPCT[i][0].c_str(); //Etiqueta criterio [renglon]
            }

		}

		return true;

	}
	catch (const exception& e)
	{

		return true;

	}

}

//INGRESAR MATRIZ DE CRITERIOS DESDE PARAMETRO (TEXTUAL)
bool Pct::IngresarDatos(string smpct)
{

	try
	{

		//Cargar en arreglo las filas de la matriz de criterios pasados como parametro
        if (!smpct.empty())
        {
			char buffer[1024];
			char* record, * line;
			int ren = 0, col = 0;
			char* end_str;

			////Carga valor de parametro (matriz CSV igual que archivo)
			char* camd = new char[smpct.length() + 1];
			strcpy(camd, smpct.c_str());

			line = strtok_r(camd, ";", &end_str);

			while (line != NULL)
			{
				char* end_token;
				record = strtok_r(line, ",", &end_token);
				while (record != NULL)
				{
					sMatrizPCT[ren][col] = record; //elemento matriz entrada
					record = strtok_r(NULL, ",", &end_token);

					col++;
				}
				col = 0;
				ren++;

				line = strtok_r(NULL, ";", &end_str);

            }

			//Distribuye información pasada como parametro en matrices correspondientes
			for (int i = 1; i <= NOCRITERIOS; i++)
			{
				for (int j = 1; j <= NOCRITERIOS; j++)
				{
					MatrizPCT[i - 1][j - 1] = atof(sMatrizPCT[i][j].c_str()); //Valor [renglon][columna]
                }
                VectorCriterios[i-1] = sMatrizPCT[i][0].c_str(); //Etiqueta criterio [renglon]
            }

        }
		return true;

	}
	catch (const exception& e)
	{

		return false;

	}

}

//CALCULA PESOS DE LOS CRITERIOS
string Pct::CalcularPesos()
{

    //-1 Menos importante
    // 0 Igual de importante
    // 1 Más importante

    int iAcuFila = 0;
    int iTotalRtGmas1 = 0;

    char output[50];

    for (int x = 0; x < NOCRITERIOS; x++)
    {
        MatrizPCT[x][NOCRITERIOS] = 0;
        MatrizPCT[x][NOCRITERIOS+1] = 0;
        MatrizPCT[x][NOCRITERIOS+2] = 0;
    }

    for (int x = 0; x < NOCRITERIOS; x++)
    {
        iAcuFila = 0;
        for (int y = 0; y < NOCRITERIOS; y++)
        {
            if ( (x!=y) && (MatrizPCT[x][y] == 1) )
                iAcuFila++;
        }
        MatrizPCT[x][NOCRITERIOS] = iAcuFila;     //RtG (score fila)
        MatrizPCT[x][NOCRITERIOS+1] = (iAcuFila + 1); //RtG+1 (score fila + 1)
    }

    for (int x = 0; x < NOCRITERIOS; x++)
        iTotalRtGmas1 += MatrizPCT[x][NOCRITERIOS + 1]; //suma de todos los score

    for (int x = 0; x < NOCRITERIOS; x++)
        MatrizPCT[x][NOCRITERIOS + 2] = MatrizPCT[x][NOCRITERIOS + 1]/ iTotalRtGmas1; //peso de criterio

    for (int x = 0; x < NOCRITERIOS; x++)
    {
        sPesosPCT += VectorCriterios[x] + ":";
        sprintf(output, "%.3f", MatrizPCT[x][NOCRITERIOS + 2]);
        sPesosPCT += output;
        sPesosPCT += "\n";
    }

    return sPesosPCT;
}
