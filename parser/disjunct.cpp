#include "disjunct.h"

Disjunct::Disjunct()
{
    literals.clear();
    name = "";
    type = init;
}

void Disjunct::print() {
    cout << "Disjunct name: " << name << endl;
    cout << "Disjunct type: ";
    (type == hypothesis) ? cout << "hypothesis" << endl : cout << "negated conjecture" << endl;
    cout << "Disjunct literals: " << endl << endl;
    for (int i = 0; i < literals.size(); ++i) {
        literals[i].print();

    }
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
    Disjunct disjunct;
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
            name = word;
            break;
        }
        case first: {
            string word = "";
            while (cnf[j] != ',')
                word += cnf[j++];
            type = (word == "hypothesis") ? hypothesis : negated_conjecture;
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
    disjunct.print();
    return disjunct;
}
