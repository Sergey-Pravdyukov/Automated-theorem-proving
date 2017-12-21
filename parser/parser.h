#pragma once

#include "literal.h"

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

class Parser {
public:
    Parser(const char *file);

    void parse();

private:

    enum DisjunctType {
        hypothesis,
        negated_conjecture
    };

    struct Disjunct {
        vector <Literal> literals;
        string name;
        DisjunctType type;
    };

    void parseCNF(int i);
    void buildDisjunct(string cnf);
    void transformToOne_lineCNF(int i);
    void printCnfs();

    static const int maxTextSize = 1e3;
    static const int maxStringLength = 1e3;
    
    FILE *ptrFile = nullptr;
    vector <string> text;
    vector <string> cnfs;
    int textStringsAmount = 0;
    int cnfsAmount = 0;
    
    vector <Disjunct> disjuncts;
};
