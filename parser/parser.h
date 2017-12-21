#pragma once

#include "disjunct.h"

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

class Parser {
public:

    void parse(const char *file);

private:

    void readFromFile(const char *file);
    void parseCNF(int i);
    void buildDisjunct(string cnf);
    void transformToOne_lineCNF(int i);
    void printCnfs();
    
    FILE *ptrFile = nullptr;
    vector <string> text;
    vector <string> cnfs;
    vector <Disjunct> disjuncts;
};
