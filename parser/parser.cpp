#include "parser.h"

Parser::Parser(const char *fname) {
    ptrFile = freopen("PUZ001-1.p", "r", stdin);
    char currentString[maxStringLength];
    if (ptrFile == NULL)
        perror("Error opening file");
    else
        while (fgets(currentString, maxStringLength, ptrFile) != nullptr)
            concat(currentString);
}

Parser::~Parser() {
    fclose(ptrFile);
}

bool isEqualsString(const char* a, const char* b) {
    if (strlen(a) == strlen(b)) {
        const int length = strlen(a);
        for (int i = 0; i < length; ++i)
            if (a[i] != b[i])
                return false;
        return true;
    }
    return false;
}

std::string removeUnnecessaryBrackets(std::string expression) {
    while (expression[0] == '(')
        expression.erase(expression.begin(), expression.begin() + 1);
    int balance = 0;
    for (int i = 0; i < expression.size(); ++i)
        balance += (expression[i] == '(') - (expression[i] == ')');
    if (balance > 0)
        expression.erase(expression.begin(), expression.begin() + balance);
    else if (balance < 0)
        expression.erase(expression.end() + balance, expression.end());
    return expression;
}

void Parser::buildDisjunct(char *cnf) {
    enum CommaOrder {
        init,
        first,
        second
    };
    Disjunct disjunct;
    Literal literal = {"", assertion};
    CommaOrder commaOrder = init;
    for (int j = 0; j < strlen(cnf); ++j) {
        if (cnf[j - 1] == ',')
            commaOrder = static_cast<CommaOrder>(std::min(static_cast<int>(commaOrder) + 1, 2));
        switch (commaOrder) {
        case first: {
            std::string word = "";
            while (cnf[j] != ',')
                word += cnf[j++];
            disjunct.type = (word == "hypothesis") ? hypothesis : negated_conjecture;
            break;
        }
        case second: {
            std::cout << cnf[j];
            if (cnf[j] != '|' && cnf[j] != '~')
                literal.name += cnf[j];
            else if (cnf[j] == '~')
                literal.type = negation;
            else {
                literal.name = removeUnnecessaryBrackets(literal.name);
                disjunct.literals.push_back(literal);
                literal = {"", assertion};
            }
            break;
        }
        }
    }
    if (literal.name != "") {
        literal.name = removeUnnecessaryBrackets(literal.name);
        disjunct.literals.push_back(literal);
    }
    std::cout << std::endl;
    std::cout << "Disjunct type: ";
    (disjunct.type == hypothesis) ? std::cout << "hypothesis" << std::endl : std::cout << "negated conjecture" << std::endl;
    std::cout << "Disjunct literals: " << std::endl;
    for (int i = 0; i < disjunct.literals.size(); ++i) {
        std::cout << "Literal type: ";
        (disjunct.literals[i].type == assertion) ? std::cout << "assertion" << std::endl : std::cout << "negation" << std::endl;
        std::cout << "Literal: " << disjunct.literals[i].name << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void Parser::parseCNF(int i) {
    transformToOne_lineCNF(i);
    buildDisjunct(cnfs[cnfsAmount - 1]);
}

void Parser::transformToOne_lineCNF(int i) {
    cnfs[cnfsAmount] = new char[maxStringLength];
    int cnfLength = 0;
    for (;;++i)
        for (int j = 0; j < strlen(text[i]); ++j) {
            if (text[i][j] == '.') {
                ++cnfsAmount;
                return;
            }
            else if (text[i][j] != '\n' && text[i][j] != ' ')
                cnfs[cnfsAmount][cnfLength++] = text[i][j];
            else if (text[i][j] == '\n')
                continue;
        }
}

void Parser::print(char **a, const int size) {
    for (int i = 0; i < size; ++i) {
        const int length = strlen(a[i]) - 1;
        for (int j = 0; j < length; ++j)
            std::cout << a[i][j];
        std::cout << std::endl;
    }
}

void Parser::parse() {
    for (int i = 0; i < textStringsAmount; ++i) {
        if (text[i][0] == '%')
            continue;
        if (strlen(text[i]) < 3)
            continue;
        char *comparedString = new char[3];
        memcpy(comparedString, &text[i][0], 3);
        if (isEqualsString(comparedString, "cnf"))
            parseCNF(i);
    }
    std::cout << std::endl;
    print(cnfs, cnfsAmount);
}

void Parser::concat(char string[]) {
    const int length = strlen(string) - 1;
    text[textStringsAmount] = new char[length];
    for (int i = 0; i < length; ++i)
        text[textStringsAmount][i] = string[i];
    ++textStringsAmount;
}

