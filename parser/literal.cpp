#include "literal.h"

Literal::Literal()
{
    name = "";
    parameters.clear();
    state = assertion;
    type = init;
}

bool Literal::operator == (Literal a) {
    if (a.parameters.size() != this->parameters.size())
        return false;
    for (int i = 0; i < a.parameters.size(); ++i)
        if (!(a.parameters[i] == this->parameters[i]))
            return false;
    return (a.state == this->state && a.type == this->type && a.name == this->name);
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

void Literal::print() {
    ofstream cout("test1.txt", ios_base::app);
    cout << "Literal state: ";
    (state == assertion) ? cout << "assertion" << endl : cout << "negation" << endl;
    cout << "Literal type: ";
    switch (type) {
    case constant: {
        cout << "constant" << " ";
        break;
    }
    case variable: {
        cout << "variable" << " ";
        break;
    }
    case function: {
        cout << "function" << " ";
        break;
    }
    default:
        break;
    }
    cout << endl;
    cout << "Literal name: " << name << endl;
    cout << endl;
    cout.close();
}

bool Literal::isContradictory(Literal a, Literal b) {
    return (a.name == b.name && a.type == b.type && a.state != b.state);
}
