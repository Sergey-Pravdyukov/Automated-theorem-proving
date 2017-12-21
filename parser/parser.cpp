#include "parser.h"

Parser::Parser(const char *fname) {
    ifstream mFile("PUZ001-1.p");
    string currentString;
        while (getline(mFile, currentString))
            text.push_back(currentString);
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

void Parser::buildDisjunct(string cnf) {
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
    cout << endl;
    cout << "Disjunct name: " << disjunct.name << endl;
    cout << "Disjunct type: ";
    (disjunct.type == hypothesis) ? cout << "hypothesis" << endl : cout << "negated conjecture" << endl;
    cout << "Disjunct literals: " << endl << endl;
    for (int i = 0; i < disjunct.literals.size(); ++i) {
        cout << "Literal state: ";
        (disjunct.literals[i].getState() == Literal::State::assertion) ? cout << "assertion" << endl : cout << "negation" << endl;
        cout << "Literal type: ";
        switch (disjunct.literals[i].getType()) {
        case Literal::Type::constant: {
            cout << "constant" << " ";
            break;
        }
        case Literal::Type::variable: {
            cout << "variable" << " ";
            break;
        }
        case Literal::Type::function: {
            cout << "function" << " ";
            break;
        }
        default:
            break;
        }
        cout << endl;
        cout << "Literal name: " << disjunct.literals[i].getName() << endl;
        cout << "Literal parameters: ";
        literal.printParameters(disjunct.literals[i].getParameters());
        cout << endl << endl;
    }
    cout << endl << endl;
    disjuncts.push_back(disjunct);
}

void Parser::parseCNF(int i) {
    transformToOne_lineCNF(i);
    buildDisjunct(cnfs[cnfs.size() - 1]);
}

void Parser::transformToOne_lineCNF(int i) {
    string currentString = "";
    for (;;++i)
        for (int j = 0; j < text[i].size(); ++j) {
            if (text[i][j] == '.') {
                cnfs.push_back(currentString);
                currentString = "";
                return;
            }
            else if (text[i][j] != '\n' && text[i][j] != ' ')
                currentString += text[i][j];
            else if (text[i][j] == '\n')
                continue;
        }
}

void Parser::printCnfs() {
    for (int i = 0; i < cnfs.size(); ++i) {
        for (int j = 0; j < cnfs[i].size(); ++j)
            cout << cnfs[i][j];
        cout << endl;
    }
}

void Parser::parse() {
    for (int i = 0; i < text.size(); ++i) {
        if (text[i][0] == '%')
            continue;
        if (text[i].size() < 3 || text[i][0] == ' ')
            continue;
        string comparedString = "";
        for (int j = 0; j < 3; ++j)
            comparedString += text[i][j];
        if (comparedString == "cnf")
            parseCNF(i);
    }
    cout << endl;
    printCnfs();
    cout << "Disjuncts amount " << disjuncts.size() << endl;
}


