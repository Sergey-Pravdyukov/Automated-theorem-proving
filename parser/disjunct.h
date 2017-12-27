#pragma once

#include "literal.h"

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Disjunct
{
public:
    Disjunct();
    Disjunct(vector <Literal> literals);

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
    static vector <Literal> merge(vector <Literal> a, vector <Literal> b);

    bool operator == (Disjunct a);

private:
    vector <Literal> literals;
    string name;
    Type type;
};
