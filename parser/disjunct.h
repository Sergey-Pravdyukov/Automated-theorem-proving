#pragma once

#include "literal.h"

#include <vector>
#include <string>

using namespace std;

class Disjunct
{
public:
    Disjunct();

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

private:
    vector <Literal> literals;
    string name;
    Type type;
};
