#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

class Literal
{
public:
    Literal();

    enum State {
        assertion,
        negation
    };

    enum Type {
        init,
        constant,
        variable,
        function
    };

    void constructLiteral(std::string formula);
    State getState();
    Type getType();
    std::string getName();
    std::vector <Literal> getParameters();
    void setState(State state);
    void setType(Type type);
    void setName(std::string name);
    void setParameters(std::vector <Literal> parameters);
    void printParameters(std::vector <Literal> parameters);
    void print();

private:
    State state;
    Type type;
    std::string name;
    std::vector <Literal> parameters;
};
