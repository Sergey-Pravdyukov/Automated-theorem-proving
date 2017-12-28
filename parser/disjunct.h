#pragma once

#include "literal.h"

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class Disjunct
{
public:
    Disjunct();
    Disjunct(vector <Literal> literals);
    Disjunct(vector <Literal> literals, string name);

    void print();

    enum Type {
        init,
        hypothesis,
        negated_conjecture
    };

    vector <Literal> getLiterals();
    string getName();
    Type getType();
    void setLiterals(vector <Literal> literals);
    void setName(string name);
    void setType(Type type);
    Disjunct buildDisjunct(string cnf);
    static Disjunct merge(Disjunct a, Disjunct b, Literal aLiteral, Literal bLiteral, const int number);
    bool isEmpty();
    void eraseLiteral(Literal a);
    bool haveSimilarLiterals();

    bool operator == (Disjunct a);

private:
    vector <Literal> literals;
    string name;
    Type type;
};
