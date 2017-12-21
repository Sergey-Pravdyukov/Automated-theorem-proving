#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <iostream>

class Literal
{
public:
    Literal();

    enum LiteralState {
        assertion,
        negation
    };

    enum LiteralType {
        init,
        constant,
        variable,
        function
    };

    void constructLiteral(std::string formula);
    LiteralState getState();
    LiteralType getType();
    std::string getName();
    std::vector <Literal> getParameters();
    void setState(LiteralState state);
    void setType(LiteralType type);
    void setName(std::string name);
    void setParameters(std::vector <Literal> parameters);
    void printParameters(std::vector <Literal> parameters);

private:
//    Literal constructLiteral(std::string formula);

    LiteralState state;
    LiteralType type;
    std::string name;
    std::vector <Literal> parameters; // простой вариант, когда нет вложенных функциональных символов
};
