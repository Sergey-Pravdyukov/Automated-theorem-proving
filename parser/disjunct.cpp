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

Disjunct::Disjunct(vector<Literal> literals, string name) {
    this->literals = literals;
    this->name = name;
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
    ofstream cout("test1.txt", ios_base::app);
    cout << "Disjunct name: " << name << endl;
    cout << "Disjunct type: ";
    (type == hypothesis) ? cout << "hypothesis" << endl : cout << "negated conjecture" << endl;
    cout << "Disjunct literals: " << endl;
    for (int i = 0; i < literals.size(); ++i)
        literals[i].print();
    cout << endl << endl;
    cout.close();
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

bool isSuitableLetter (char a) {
    return  isalpha(a) || a == '_' || isdigit(a);
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
            do {
                if (isSuitableLetter(cnf[j]))
                    word += cnf[j];
            } while (cnf[++j] != ',');
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
    return disjunct;
}

Disjunct Disjunct::merge(Disjunct a, Disjunct b, Literal aLiteral, Literal bLiteral, const int number) {
    vector <Literal> aLiterals = a.getLiterals();
    vector <Literal> result;
    result.clear();
    for (int i = 0; i < aLiterals.size(); ++i)
        if (!(aLiteral == aLiterals[i]))
            result.push_back(aLiterals[i]);
    vector <Literal> bLiterals = b.getLiterals();
    for (int i = 0; i < bLiterals.size(); ++i) {
        if (bLiteral == bLiterals[i])
            continue;
        if (find(result.begin(), result.end(), bLiterals[i]) == result.end())
            result.push_back(bLiterals[i]);
    }
    return Disjunct(result, "clause_" + to_string(number));
}

bool Disjunct::isEmpty() {
    return literals.size() == 0;
}

void Disjunct::eraseLiteral(Literal a) {
    literals.erase(find(literals.begin(), literals.end(), a));
}

bool Disjunct::haveSimilarLiterals() {
    for (int i = 0; i < literals.size(); ++i)
        for (int j = 0; j < literals.size(); ++j)
            if (i != j && literals[i] == literals[j])
                return true;
    return false;
}
