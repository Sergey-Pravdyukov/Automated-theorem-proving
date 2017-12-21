#include "literal.h"

Literal::Literal()
{
    name = "";
    parameters.clear();
    state = assertion;
    type = init;
}

Literal::State Literal::getState() {
    return this->state;
}

void Literal::setState(State state) {
    this->state = state;
}

Literal::Type Literal::getType() {
    return this->type;
}

void Literal::setType(Type type) {
    this->type = type;
}

std::string Literal::getName() {
    return this->name;
}

void Literal::setName(std::string name) {
    this->name = name;
}

std::vector <Literal> Literal::getParameters() {
    return this->parameters;
}

void Literal::setParameters(std::vector<Literal> parameters) {
    this->parameters.clear();
    for (int i = 0; i < parameters.size(); ++i)
        this->parameters.push_back(parameters[i]);
}

void Literal::printParameters(std::vector<Literal> parameters) {
    for (int i = 0; i < parameters.size(); ++i) {
        if (parameters[i].parameters.size() == 0)
            std::cout << parameters[i].name << " ";
        else {
            std::cout << parameters[i].name << "(";
            printParameters(parameters[i].parameters);
        }
    }
}

std::string getFunctionNameFromString(std::string formula) {
    int i = 0;
    std::string result = "";
    while (formula[i] != '(')
        result += formula[i++];
    return result;
}

std::vector <Literal> getParametersFromString(std::string formula) {
    int i = 0;
    std::vector <Literal> result;
    std::string atomicFormula = "";
    Literal literal = Literal();
    while (formula[i++] != '(') {}
    while (formula[i] != ')') {
        if (formula[i] == ',') {
            literal.constructLiteral(atomicFormula);
            result.push_back(literal);
            atomicFormula = "";
        }
        else
            atomicFormula += formula[i];
        ++i;
    }
    if (atomicFormula != "") {
        literal.constructLiteral(atomicFormula);
        result.push_back(literal);
    }
    return result;
}

void Literal::constructLiteral(std::string formula) {
    if (isupper(formula[0])) {
        type = variable;
        name = formula;
    }
    else if (formula[formula.size() - 1] != ')') {
        type = constant;
        name = formula;
    }
    else {
        type = function;
        name = getFunctionNameFromString(formula);
        parameters = getParametersFromString(formula);
    }
}
