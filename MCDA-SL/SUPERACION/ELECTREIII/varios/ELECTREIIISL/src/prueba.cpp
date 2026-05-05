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
#include "../LIB/utilerias/utilerias.hpp"

using namespace std;
char FILENAME[250];

string LoadFile(char sFILENAME[])
{
    ifstream t(sFILENAME);
    stringstream buffer;
    buffer << t.rdbuf();
    string sTmp = buffer.str();
    findAndReplaceAll(sTmp, "\n","");
    return sTmp;
}

int main(int argc, char** argv) {
    ElectreIII E(5,5,-1);
    strcpy(FILENAME,"D:\\artesanias.csv");
    E.EnterData(LoadFile(FILENAME));
    E.Build();
    cout << "NET FLOW RESULTS:\n" << E.ExploitNetFlow() + "\n";
    cout << "DISTILLATION RESULTS:\n" << E.ExploitDistillation() + "\n";
    return 0;
}
