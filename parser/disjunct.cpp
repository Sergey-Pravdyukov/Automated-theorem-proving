#include "disjunct.h"

Disjunct::Disjunct()
{
    literals.clear();
    name = "";
    type = init;
}

Disjunct::Disjunct(vector<Literal> literals) {
    this->literals = literals;
    name = "";
    type = init;
}

bool Disjunct::operator == (Disjunct a) {
    if (a.literals.size() != this->literals.size())
        return false;
    for (int i = 0; i < a.literals.size(); ++i)
        if (!(a.literals[i] == this->literals[i]))
            return false;
    return (a.name == this->name && a.type == this->type);
}

vector <Literal> Disjunct::getLiterals() {
    return literals;
}

void Disjunct::print() {
    cout << "Disjunct name: " << name << endl;
    cout << "Disjunct type: ";
    (type == hypothesis) ? cout << "hypothesis" << endl : cout << "negated conjecture" << endl;
    cout << "Disjunct literals: " << endl;
    for (int i = 0; i < literals.size(); ++i)
        literals[i].print();
    cout << endl << endl;
}

void removeUnnecessaryBrackets(string &expression) {
    while (expression[0] == '(')
        expression.erase(expression.begin(), expression.begin() + 1);
    int balance = 0;
    for (int i = 0; i < expression.size(); ++i)
        balance += (expression[i] == '(') - (expression[i] == ')');
    if (balance > 0)
        expression.erase(expression.begin(), expression.begin() + balance);
    else if (balance < 0)
        expression.erase(expression.end() + balance, expression.end());
}

Disjunct Disjunct::buildDisjunct(string cnf) {
    enum CommaOrder {
        init,
        first,
        second
    };
    Disjunct disjunct = Disjunct();
    Literal literal = Literal();
    CommaOrder commaOrder = init;
    const int initialIndex = 4;
    string stringLiteralName = "";
    for (int j = initialIndex; j < cnf.size(); ++j) {
        if (cnf[j - 1] == ',')
            commaOrder = static_cast<CommaOrder>(min(static_cast<int>(commaOrder) + 1, 2));
        switch (commaOrder) {
        case init: {
            string word = "";
            while (cnf[j] != ',')
                if (isalpha(cnf[j]) || cnf[j] == '_')
                    word += cnf[j++];
            disjunct.name = word;
            break;
        }
        case first: {
            string word = "";
            while (cnf[j] != ',')
                word += cnf[j++];
            disjunct.type = (word == "hypothesis") ? hypothesis : negated_conjecture;
            break;
        }
        case second: {
            if (cnf[j] != '|' && cnf[j] != '~')
                stringLiteralName += cnf[j];
            else if (cnf[j] == '~')
                literal.setState(Literal::State::negation);
            else {
                removeUnnecessaryBrackets(stringLiteralName);
                literal.constructLiteral(stringLiteralName);
                disjunct.literals.push_back(literal);
                literal = Literal();
                stringLiteralName = "";
            }
            break;
        }
        }
    }
    if (stringLiteralName != "") {
        removeUnnecessaryBrackets(stringLiteralName);
        literal.constructLiteral(stringLiteralName);
        disjunct.literals.push_back(literal);
    }
//    disjunct.print();
    return disjunct;
}

vector <Literal> Disjunct::merge(vector<Literal> a, vector<Literal> b) {
    vector <Literal> result;
    result.clear();
    for (int i = 0; i < a.size(); ++i) {
        bool isFind = false;
        for (int j = 0; j < b.size(); ++j)
            if (Literal::isContradictory(a[i], b[j]))
                isFind = true;
        if (isFind == false)
            result.push_back(a[i]);
    }
    for (int i = 0; i < b.size(); ++i) {
        bool isFind = false;
        for (int j = 0; j < a.size(); ++j)
            if (Literal::isContradictory(b[i], a[j]))
                isFind = true;
        if (isFind == false)
            result.push_back(b[i]);
    }
    return result;
}
