#pragma once

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

class Parser
{
public:
    Parser(const char *file);
    ~Parser();

    void parse();

private:

    enum DisjunctType {
        hypothesis,
        negated_conjecture
    };

    enum LiteralType {
        assertion,
        negation
    };

    struct Literal {
        std::string name;     // Исправить в дальнейшем, учитывая случай, когда литер имеет вид f(x,y),
                              // то есть парсить название функции отдельно от ее аргументов
        LiteralType type;
    };

    struct Disjunct {
        std::vector <Literal> literals;
        std::string name;
        DisjunctType type;
    };

    void concat(char string[]);
    void parseCNF(int i);
    void buildDisjunct(char *cnf);
    void transformToOne_lineCNF(int i);
    void print(char **array, const int size);

    static const int maxTextSize = 1e3;
    static const int maxStringLength = 1e3;
    
    FILE *ptrFile = nullptr;
    char **text = new char*[maxTextSize];
    char **cnfs = new char*[maxTextSize];
    int textStringsAmount = 0;
    int cnfsAmount = 0;
    
    std::vector <Disjunct> disjuncts;
};
