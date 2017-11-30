#pragma once

#include <cstdio>
#include <iostream>
#include <cstring>

class Parser
{
public:
    Parser(const char *file);
    ~Parser();

    void parse();

private:
    void concat(char []);

    static const int maxTextSize = 1e3;
    static const int maxStringLehgth = 100;
    
    FILE *ptrFile = nullptr;
    char **text = new char*[maxTextSize];
    int size = 0;
};
